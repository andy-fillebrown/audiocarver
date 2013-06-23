/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
**
** Contact: Andy Fillebrown (andy.fillebrown@gmail.com)
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file.  Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#include "ac_csound_audioengine.h"
#include <ac_audioengine_sink.h>
#include <ac_core_namespace.h>
#include <mi_audioengine_scopedsettingschange.h>
#include <mi_audioengine_settings.h>
#include <mi_audioengine_utilities.h>
#include <mi_core_utilities.h>
#include <idatabase.h>
#include <imodel.h>
#include <imodelitem.h>
#include <icore.h>
#include <csound.h>
#include <QAudioDeviceInfo>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QThread>
#include <QTimer>
#include <QtDebug>
#include <QtEndian>

using namespace Ac;
using namespace Ac::AudioEngine;
using namespace Mi;

static bool databaseIsSaved()
{
    return !IDatabase::instance()->fileName().isEmpty();
}

static QString rootDirectoryName()
{
    const QString db_file_name = IDatabase::instance()->fileName();
    if (db_file_name.isEmpty())
        return "";
    return QFileInfo(db_file_name).path();
}

static QDir rootDirectory()
{
    return QDir(rootDirectoryName());
}

static QString outputFileDirectoryName()
{
    IDatabase *database = IDatabase::instance();
    const QString database_file_name = database->fileName();
    if (database_file_name.isEmpty())
        return "";
    QDir root_dir = rootDirectory();
    IModelItem *project_settings = database->rootItem()->findItem(ProjectSettingsItem);
    QString output_dir_name = get<QString>(project_settings, OutputDirectoryRole);
    if (output_dir_name.isEmpty())
        output_dir_name = database_file_name + "-output";
    if (!root_dir.mkpath(output_dir_name)) {
        qDebug() << Q_FUNC_INFO << ": Error making path" << output_dir_name;
        return "";
    }

    return output_dir_name;
}

static QString audioFileDirectoryName()
{
    return outputFileDirectoryName() + "/audio";
}

static QString playbackFileDirectory()
{
    QDir root_dir = rootDirectory();
    const QString csound_dir_name = outputFileDirectoryName() + "/csound";
    if (!root_dir.mkpath(csound_dir_name)) {
        qDebug() << Q_FUNC_INFO << ": Error making path" << csound_dir_name;
        return "";
    }
    return csound_dir_name;
}

static QString playbackOrcFileName()
{

    return playbackFileDirectory() + "/playback.orc";
}

static QString playbackScoFileName()
{
    return playbackFileDirectory() + "/playback.sco";
}

namespace Csound {

static qint64 audioSinkCallback(char *data, qint64 byteCount);

class AudioEnginePrivate;
AudioEnginePrivate *d_instance = 0;

class AudioEnginePrivate : public Base::AudioEnginePrivate
{
public:
    AudioEngine *q;
    Sink *sink;
    CSOUND *csound;
    float *csoundBuffer;
    long csoundBufferSize;
    int currentSample;
    AudioEngineSettings settings;
    int sampleSize;
    int sampleRate;
    int controlRate;
    int bufferSize;
    int bytesPerSample;
    QAudioFormat::SampleType sampleType;
    QAudioFormat::Endian byteOrder;
    qreal scoreVolume;
    int trackCount;
    qreal startTime;
    QString compiledDatabase;
    QString previousTrackName;
    qreal previousTrackVolume;
    uint compileFailed : 1;
    uint compiled : 1;
    uint started : 1;
    uint connected : 1;
    uint stopping : 1;
    int scoreDone;
    QTimer *stopTimer;
    QTimer *compileTimer;

    AudioEnginePrivate(AudioEngine *q)
        :   q(q)
        ,   sink(0)
        ,   csound(0)
        ,   csoundBuffer(0)
        ,   csoundBufferSize(0)
        ,   currentSample(0)
        ,   sampleSize(0)
        ,   sampleRate(0)
        ,   controlRate(0)
        ,   bufferSize(0)
        ,   bytesPerSample(0)
        ,   sampleType(QAudioFormat::SignedInt)
        ,   byteOrder(QAudioFormat::LittleEndian)
        ,   scoreVolume(1.0f)
        ,   trackCount(0)
        ,   startTime(0.0)
        ,   previousTrackVolume(-1.0f)
        ,   compileFailed(false)
        ,   compiled(false)
        ,   started(false)
        ,   connected(false)
        ,   stopping(false)
        ,   scoreDone(0)
        ,   stopTimer(0)
        ,   compileTimer(new QTimer)
    {
        d_instance = this;
        csoundInitialize(0, 0, 0);
        csound = csoundCreate(0);
        if (!csound)
            qDebug() << Q_FUNC_INFO << ": Error creating csound";
        const QString opcodeDir = Mi::applicationTreeDirectory();
        const QByteArray opcodeDir_ba = opcodeDir.toLocal8Bit();
        csoundSetGlobalEnv("OPCODEDIR", opcodeDir_ba.constData());
        settings.read(Core::ICore::instance()->settings());
        compile();
        compileTimer->setSingleShot(true);
        scoreVolume = get<qreal>(IDatabase::instance()->rootItem(), VolumeRole);
        IModel *model = IModel::instance();
        connect(model, SIGNAL(modelReset()), SLOT(reset()));
        connect(model, SIGNAL(dataAboutToBeChanged(IModelItem*,int)), SLOT(dataAboutToBeChanged(IModelItem*)));
        connect(model, SIGNAL(dataChanged(IModelItem*,int)), SLOT(dataChanged(IModelItem*,int)));
        connect(model, SIGNAL(itemInserted(IModelItem*,int)), SLOT(itemChanged(IModelItem*)));
        connect(model, SIGNAL(itemRemoved(IModelItem*,int)), SLOT(itemChanged(IModelItem*)));
        connect(compileTimer, SIGNAL(timeout()), SLOT(compile()));
    }

    ~AudioEnginePrivate()
    {
        stop();
        if (csound)
            csoundDestroy(csound);
        delete compileTimer;
        delete sink;
        settings.write(Core::ICore::instance()->settings());
    }

    void reset()
    {
        compiledDatabase = "";
        compiled = false;
    }

    void dataAboutToBeChanged(IModelItem *item)
    {
        if (TrackItem != item->itemType())
            return;
        previousTrackName = get<QString>(item, NameRole);
        previousTrackVolume = get<qreal>(item, VolumeRole);
    }

    void dataChanged(IModelItem *item, int role)
    {
        if (TrackItem == item->itemType()) {
            if (previousTrackName != get<QString>(item, NameRole)
                    || previousTrackVolume != get<qreal>(item, VolumeRole)) {
                compiled = false;
                compileTimer->start();
            }
        } else if (ScoreItem == item->itemType()) {
            scoreVolume = get<qreal>(item, VolumeRole);
            if (StartTimeRole == role)
                q->setStartTime(get<qreal>(item, StartTimeRole));
        }
    }

    void itemChanged(IModelItem *item)
    {
        if (ListItem != item->itemType())
            return;
        if (TrackItem != get<int>(item, ListTypeRole))
            return;
        q->setTrackCount(item->itemCount());
    }

    void compile()
    {
        compileFailed = false;
        if (compiledDatabase != IDatabase::instance()->fileName())
            compiled = false;
        if (compiled)
            return;
        if (!csound || !databaseIsSaved()) {
            compileFailed = true;
            return;
        }
        stop();
        csoundBuffer = 0;
        csoundBufferSize = 0;
        QAudioDeviceInfo device_info = Mi::AudioEngine::deviceInfo(settings.deviceName());
        QAudioFormat format;
        format.setChannelCount(2);
        format.setCodec("audio/pcm");
        format.setSampleRate(settings.sampleRate());
        format.setSampleSize(settings.sampleSize());
        format.setSampleType(QAudioFormat::SignedInt);
        delete sink;
        sink = new Sink(device_info, format, bufferSize, audioSinkCallback);
        format = sink->format();
        sampleSize = format.sampleSize();
        sampleRate = format.sampleRate();
        controlRate = settings.controlRate();
        bufferSize = settings.bufferSize();
        bytesPerSample = sampleSize / 8;
        sampleType = format.sampleType();
        byteOrder = format.byteOrder();
        const QString &orc_file_name = playbackOrcFileName();
        const QString &sco_file_name = playbackScoFileName();
        if (!writePlaybackOrc(orc_file_name)
                || !writePlaybackSco(sco_file_name)) {
            compileFailed = true;
            return;
        }
        csoundReset(csound);
        if (CSOUND_SUCCESS != csoundPreCompile(csound)) {
            qDebug() << Q_FUNC_INFO << ": Error precompiling csound";
            compileFailed = true;
            return;
        } else
            csoundSetHostImplementedAudioIO(csound, 1, bufferSize);
        char first_arg[] = "";
        char output_arg[] = "-+rtaudio=null";
        char displays_arg[] = "-d";
        const QString sample_rate_flag = QString("-r%1").arg(sampleRate);
        QByteArray sample_rate_flag_ba = sample_rate_flag.toLocal8Bit();
        char *sample_rate_arg = sample_rate_flag_ba.data();
        const QString control_rate_flag = QString("-k%1").arg(controlRate);
        QByteArray control_rate_flag_ba = control_rate_flag.toLocal8Bit();
        char *control_rate_arg = control_rate_flag_ba.data();
        QByteArray orc_file_ba = orc_file_name.toLocal8Bit();
        char *orc_arg = orc_file_ba.data();
        QByteArray sco_file_ba = sco_file_name.toLocal8Bit();
        char *sco_arg = sco_file_ba.data();
        const int argc = 7;
        char *argv[] = { first_arg, output_arg, displays_arg, sample_rate_arg, control_rate_arg, orc_arg, sco_arg };
        for (int i = 1;  i < argc;  ++i)
            qDebug() << Q_FUNC_INFO << "arg" << i << "==" << argv[i];
        if (CSOUND_SUCCESS != csoundCompile(csound, argc, argv)) {
            qDebug() << Q_FUNC_INFO << ": Error compiling csound";
            compileFailed = true;
            return;
        } else {
            csoundBuffer = csoundGetOutputBuffer(csound);
            if (!csoundBuffer) {
                qDebug() << Q_FUNC_INFO << ": Error getting csound buffer";
                compileFailed = true;
                return;
            }
        }
        compiledDatabase = IDatabase::instance()->fileName();
        compiled = true;
    }

    bool writePlaybackOrc(const QString &fileName)
    {
        QFile orc_file(fileName);
        if (!orc_file.open(QIODevice::WriteOnly))
            return false;
        QTextStream stream(&orc_file);
        stream  << "0dbfs = 1" << endl
                << "nchnls = 1" << endl
                << endl
                << "instr 1" << endl
                << "    i_volume = p6" << endl
                << "    a_out diskin2 p4, 1, p5, 0, 0, 0, 1024" << endl
                << "    out i_volume * a_out" << endl
                << "endin" << endl;
        orc_file.close();
        return true;
    }

    bool writePlaybackSco(const QString &fileName)
    {
        QFile sco_file(fileName);
        if (!sco_file.open(QIODevice::WriteOnly))
            return false;
        IModelItem *score = IDatabase::instance()->rootItem();
        IModelItem *project_settings = score->findItem(ProjectSettingsItem);
        QString audio_file_type = get<QString>(project_settings, AudioFileTypeRole);
        if (audio_file_type.isEmpty()) {
#           ifdef Q_OS_MAC
            {   audio_file_type = "aiff";
            }
#           else
            {   audio_file_type = "wav";
            }
#           endif
        }
        IModelItem *track_list = score->findItem(TrackListItem);
        const int n = track_list->itemCount();
        Q_ASSERT(n == trackCount);
        const QString audio_dir_name = audioFileDirectoryName();
        int sub_instrument = 1;
        for (int i = 0;  i < n;  ++i) {
            IModelItem *track = track_list->itemAt(i);
            const QString track_name = get<QString>(track, NameRole).toLower();
            const QString audio_file_name = audio_dir_name + "/" + track_name + "." + audio_file_type;
            const QString sco_line = QString("i1.%1 0 -1 \"%2\" %3 %4\n")
                    .arg(sub_instrument)
                    .arg(audio_file_name)
                    .arg(startTime)
                    .arg(get<qreal>(track, VolumeRole));
            sco_file.write(qPrintable(sco_line));
            sub_instrument++;
            if ((sub_instrument % 10) == 0)
                sub_instrument++;
        }
        const qreal score_length = get<qreal>(score, LengthRole) - get<qreal>(score, StartTimeRole);
        const QString sco_end = QString("e %1").arg(score_length);
        sco_file.write(qPrintable(sco_end));
        sco_file.write("\n");
        sco_file.close();
        return true;
    }

    void start()
    {
        if (!csound)
            return;
        if (started)
            return;
        if (!compiled)
            compileTimer->start();
        while (!compiled) {
            if (compileFailed)
                return;
            QThread::yieldCurrentThread();
        }
        started = true;
        sink->start();
    }

    void stop()
    {
        if (!started)
            return;
        stopping = true;
        sink->stop();
        delete stopTimer;
        stopTimer = 0;
        stopping = false;
        currentSample = 0;
        csoundRewindScore(csound);
        scoreDone = 0;
        started = false;
        connected = false;
    }

    qint64 read(char *data, qint64 byteCount)
    {
        if (!connected) {
            stopTimer = new QTimer;
            stopTimer->setSingleShot(true);
            connect(stopTimer, SIGNAL(timeout()), SLOT(stop()));
            connected = true;
        }

        // The csound_buffer_size variable contains the number of bytes that
        // would be in the csound output buffer if it contained sampleSize
        // samples instead of float or double samples.
        if (0 == csoundBufferSize)
            csoundBufferSize = bytesPerSample * csoundGetOutputBufferSize(csound);
        if (0 == csoundBufferSize) {
            qDebug() << Q_FUNC_INFO << ": Csound buffer size is zero";
            csoundBufferSize = -1;
        }
        if (csoundBufferSize <= 0)
            return byteCount;

        uchar *output_data = reinterpret_cast<uchar*>(data);
        qint64 bytes_read = 0;
        while (bytes_read < byteCount) {
            if (currentSample == 0 && !scoreDone)
                scoreDone = csoundPerformBuffer(csound);
            float *csound_data = csoundBuffer + currentSample;

            // 'n' will be the number of bytes to be read from the csound buffer.
            int n = 0;
            if (currentSample == 0) {
                if ((bytes_read + csoundBufferSize) < byteCount)
                    n = csoundBufferSize;
                else {
                    n = byteCount - bytes_read;
                    currentSample += n / bytesPerSample;
                }
            } else {
                const int current_byte = bytesPerSample * currentSample;
                if ((bytes_read + (csoundBufferSize - current_byte)) < byteCount) {
                    n = csoundBufferSize - current_byte;
                    currentSample = 0;
                } else {
                    n = byteCount - bytes_read;
                    currentSample += n / bytesPerSample;
                }
            }

            bytes_read += n;
            while (n) {
                const float x = scoreVolume * *csound_data;
                if (8 == sampleSize) {
                    if (QAudioFormat::UnSignedInt == sampleType) {
                        const quint8 value = static_cast<quint8>((1.0f + x) / 2.0f * 255.0f);
                        *reinterpret_cast<quint8*>(output_data) = value;
                    } else if (QAudioFormat::SignedInt == sampleType) {
                        const qint8 value = static_cast<qint8>(x * 127.0f);
                        *reinterpret_cast<quint8*>(output_data) = value;
                    }
                } else if (16 == sampleSize) {
                    if (QAudioFormat::UnSignedInt == sampleType) {
                        quint16 value = static_cast<quint16>((1.0f + x) / 2.0f * 65535.0f);
                        if (QAudioFormat::LittleEndian == byteOrder)
                            qToLittleEndian<quint16>(value, output_data);
                        else
                            qToBigEndian<quint16>(value, output_data);
                    } else if (QAudioFormat::SignedInt == sampleType) {
                        qint16 value = static_cast<qint16>(x * 32767.0f);
                        if (QAudioFormat::LittleEndian == byteOrder)
                            qToLittleEndian<qint16>(value, output_data);
                        else
                            qToBigEndian<qint16>(value, output_data);
                    }
                } else if (32 == sampleSize) {
                    if (QAudioFormat::UnSignedInt == sampleType) {
                        quint32 value = static_cast<quint32>((1.0f + x) / 2.0f * 4294967295.0f);
                        if (QAudioFormat::LittleEndian == byteOrder)
                            qToLittleEndian<quint32>(value, output_data);
                        else
                            qToBigEndian<quint32>(value, output_data);
                    } else if (QAudioFormat::SignedInt == sampleType) {
                        qint32 value = static_cast<qint32>(x * 2147483647.0f);
                        if (QAudioFormat::LittleEndian == byteOrder)
                            qToLittleEndian<qint32>(value, output_data);
                        else
                            qToBigEndian<qint32>(value, output_data);
                    } else if (QAudioFormat::Float == sampleType)
                        *reinterpret_cast<float*>(output_data) = x;
                }
                ++csound_data;
                output_data += bytesPerSample;
                n -= bytesPerSample;
            }
            if (scoreDone && currentSample == 0)
                break;
        }
        if (scoreDone && !stopping)
            stopTimer->start();
        return byteCount;
    }
};

qint64 audioSinkCallback(char *data, qint64 byteCount)
{
    return d_instance->read(data, byteCount);
}

static AudioEngine *instance = 0;

AudioEngine *AudioEngine::instance()
{
    return Csound::instance;
}

AudioEngine::AudioEngine()
    :   d(new AudioEnginePrivate(this))
{
    Csound::instance = this;
    ::AudioEngine::ScopedSettingsChange settings_change(this);
}

AudioEngine::~AudioEngine()
{
    Csound::instance = 0;
    delete d;
}

const AudioEngineSettings &AudioEngine::settings() const
{
    return d->settings;
}

void AudioEngine::setSettings(const AudioEngineSettings &settings)
{
    if (d->settings == settings)
        return;
    ::AudioEngine::ScopedSettingsChange settings_change(this);
    d->settings = settings;
    d->compile();
    settings.write(Core::ICore::instance()->settings());
}

int AudioEngine::trackCount() const
{
    return d->trackCount;
}

void AudioEngine::setTrackCount(int count)
{
    if (count == d->trackCount)
        return;
    d->trackCount = count;
    d->compiled = false;
    d->compileTimer->start();
}

qreal AudioEngine::startTime() const
{
    return d->startTime;
}

void AudioEngine::setStartTime(qreal time)
{
    if (d->startTime == time)
        return;
    if (isStarted())
        stop();
    d->startTime = time;
    d->compiled = false;
    d->compileTimer->start();
}

bool AudioEngine::isStarted() const
{
    return d->started;
}

void AudioEngine::start()
{
    d->start();
}

void AudioEngine::stop()
{
    d->stop();
}

void AudioEngine::compile()
{
    d->compileTimer->start();
}

}
