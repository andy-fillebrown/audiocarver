/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include <ac_csoundaudioengine.h>

#include <ac_audioenginesettings.h>
#include <ac_audioengineutils.h>
#include <ac_audiosink.h>
#include <ac_namespace.h>

#include <mi_coreutils.h>
#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <icore.h>

#include <csound.h>

#include <QAudioDeviceInfo>

#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QTimer>
#include <QtEndian>

class CsoundAudioEnginePrivate;

CsoundAudioEnginePrivate *d_instance = 0;
static qint64 audioSinkCallback(char *data, qint64 byteCount);

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
    const QString db_file_name = IDatabase::instance()->fileName();
    if (db_file_name.isEmpty())
        return "";

    QDir root_dir = rootDirectory();

    const IModel *model = IModel::instance();
    const IModelItem *project_settings = model->itemFromIndex(model->itemIndex(Ac::ProjectSettingsItem));

    QString output_dir_name = project_settings->data(Ac::OutputDirectoryRole).toString();
    if (output_dir_name.isEmpty())
        output_dir_name = db_file_name + "-output";
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

class CsoundAudioEnginePrivate
{
public:
    AudioSink *sink;
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
    int trackCount;
    qreal startTime;
    uint started : 1;
    uint scoreDone : sizeof(uint) - 1;
    QTimer *stopTimer;
    QTimer *trackCountTimer;

    CsoundAudioEnginePrivate()
        :   sink(0)
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
        ,   trackCount(0)
        ,   startTime(0.0)
        ,   started(false)
        ,   scoreDone(false)
        ,   stopTimer(new QTimer)
        ,   trackCountTimer(new QTimer)
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
        updateCsound();

        stopTimer->setSingleShot(true);
        trackCountTimer->setSingleShot(true);
    }

    ~CsoundAudioEnginePrivate()
    {
        stop();

        if (csound)
            csoundDestroy(csound);

        delete trackCountTimer;
        delete stopTimer;
        delete sink;

        settings.write(Core::ICore::instance()->settings());
    }

    void updateCsound()
    {
        if (!csound)
            return;

        stop();

        csoundBuffer = 0;
        csoundBufferSize = 0;

        QAudioDeviceInfo device_info = Ac::deviceInfo(settings.deviceName());
        QAudioFormat format;
        format.setChannelCount(2);
        format.setCodec("audio/pcm");
        format.setSampleRate(settings.sampleRate());
        format.setSampleSize(settings.sampleSize());
        format.setSampleType(QAudioFormat::SignedInt);
        delete sink;
        sink = new AudioSink(device_info, format, bufferSize, audioSinkCallback);
        format = sink->format();

        sampleSize = format.sampleSize();
        sampleRate = format.sampleRate();
        controlRate = settings.controlRate();
        bufferSize = settings.bufferSize();
        bytesPerSample = sampleSize / 8;
        sampleType = format.sampleType();
        byteOrder = format.byteOrder();

        csoundReset(csound);

        if (CSOUND_SUCCESS != csoundPreCompile(csound)) {
            qDebug() << Q_FUNC_INFO << ": Error precompiling csound";
            return;
        } else
            csoundSetHostImplementedAudioIO(csound, 1, bufferSize);

        const QString &orc_file_name = playbackOrcFileName();
        const QString &sco_file_name = playbackScoFileName();
        updatePlaybackOrc(orc_file_name);
        updatePlaybackSco();

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
            return;
        } else {
            csoundBuffer = csoundGetOutputBuffer(csound);
            if (!csoundBuffer) {
                qDebug() << Q_FUNC_INFO << ": Error getting csound buffer";
                return;
            }
        }
    }

    void updatePlaybackOrc(const QString &fileName)
    {
        QFile orc_file(fileName);
        if (!orc_file.open(QIODevice::WriteOnly)) {
            qDebug() << Q_FUNC_INFO << ": Error opening playback csd";
            return;
        }

        QTextStream stream(&orc_file);
        stream  << "0dbfs = 1" << endl
                << "nchnls = 1" << endl
                << endl
                << "instr 1" << endl
                << "    a_out soundin p4, p5, 0, 0, 1024" << endl
                << "    out a_out" << endl
                << "endin" << endl;

        orc_file.close();
    }

    void updatePlaybackSco()
    {
        QFile sco_file(playbackScoFileName());
        if (!sco_file.open(QIODevice::WriteOnly)) {
            qDebug() << Q_FUNC_INFO << ": Error opening playback sco file";
            return;
        }

        const IModel *model = IModel::instance();

        const IModelItem *project_settings = model->itemFromIndex(model->itemIndex(Ac::ProjectSettingsItem));
        QString audio_file_type = project_settings->data(Ac::AudioFileTypeRole).toString();
        if (audio_file_type.isEmpty())
            audio_file_type = "wav";

        const QModelIndex track_list_index = model->listIndex(Ac::TrackItem);
        const int n = model->rowCount(track_list_index);
        Q_ASSERT(n == trackCount);

        const QString audio_dir_name = audioFileDirectoryName();

        int sub_instrument = 1;
        for (int i = 0;  i < n;  ++i) {
            const IModelItem *track = model->itemFromIndex(model->index(i, model->listIndex(Ac::TrackItem)));
            const QString track_name = track->data(Mi::NameRole).toString().toLower();
            const QString audio_file_name = audio_dir_name + "/" + track_name + "." + audio_file_type;

            const QString sco_line = QString("i1.%1 0 -1 \"%2\" %3\n")
                    .arg(sub_instrument)
                    .arg(audio_file_name)
                    .arg(0);

            sco_file.write(qPrintable(sco_line));

            sub_instrument++;
            if ((sub_instrument % 10) == 0)
                sub_instrument++;
        }

        const qreal score_length = model->rootItem()->data(Ac::LengthRole).toReal();
        const QString sco_end = QString("e %1")
                .arg(score_length);
        sco_file.write(qPrintable(sco_end));

        sco_file.write("\n");
        sco_file.close();
    }

    void start()
    {
        if (!csound)
            return;
        if (started)
            return;
        started = true;
        sink->start();
    }

    void stop()
    {
        if (!started)
            return;
        sink->stop();
        currentSample = 0;
        csoundRewindScore(csound);
        scoreDone = false;
        started = false;
    }

    qint64 read(char *data, qint64 byteCount)
    {
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
                const float x = *csound_data;
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

        if (scoreDone)
            stopTimer->start();

        return byteCount;
    }
};

qint64 audioSinkCallback(char *data, qint64 byteCount)
{
    return d_instance->read(data, byteCount);
}

CsoundAudioEngine::CsoundAudioEngine()
    :   d(new CsoundAudioEnginePrivate)
{
    connect(d->stopTimer, SIGNAL(timeout()), SLOT(stop()));
    connect(d->trackCountTimer, SIGNAL(timeout()), SLOT(updateTrackCount()));
}

CsoundAudioEngine::~CsoundAudioEngine()
{
    delete d;
}

const AudioEngineSettings &CsoundAudioEngine::settings() const
{
    return d->settings;
}

void CsoundAudioEngine::setSettings(const AudioEngineSettings &settings)
{
    if (d->settings == settings)
        return;
    d->settings = settings;
    d->updateCsound();
    settings.write(Core::ICore::instance()->settings());
    emit settingsChanged();
}

int CsoundAudioEngine::trackCount() const
{
    return d->trackCount;
}

void CsoundAudioEngine::setTrackCount(int count)
{
    d->trackCount = count;
}

qreal CsoundAudioEngine::startTime() const
{
    return d->startTime;
}

void CsoundAudioEngine::setStartTime(qreal time)
{
    d->startTime = time;
}

bool CsoundAudioEngine::isStarted() const
{
    return d->started;
}

void CsoundAudioEngine::start()
{
    d->start();
}

void CsoundAudioEngine::stop()
{
    d->stop();
}

void CsoundAudioEngine::updateTrackCount()
{
    d->updatePlaybackSco();
}
