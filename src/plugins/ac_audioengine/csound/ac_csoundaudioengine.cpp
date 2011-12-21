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

#include <ac_audioengineutils.h>
#include <ac_audiosink.h>

#include <icore.h>

#include <csound.h>

#include <QAudioDeviceInfo>

#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QtEndian>

class CsoundAudioEnginePrivate;

CsoundAudioEnginePrivate *d_instance = 0;
static qint64 audioSinkCallback(char *data, qint64 byteCount);

static QString rootDirName()
{
    QDir rootDir(QCoreApplication::applicationDirPath());
    rootDir.cdUp();
    return rootDir.absolutePath() + "/";
}

static QList<int> integerMultiples(int value)
{
    QList<int> multiples;
    for (int i = 1;  i <= value;  ++i) {
        if (0 == value % i)
            multiples.append(i);
    }
    return multiples;
}

static QList<int> bufferSizes(int controlSamples, int sampleRate)
{
    QList<int> buffer_sizes;
    int cur_ctrl_samples = controlSamples;
    while (cur_ctrl_samples <= sampleRate) {
        buffer_sizes.append(cur_ctrl_samples);
        cur_ctrl_samples += controlSamples;
    }
    return buffer_sizes;
}

class CsoundAudioEnginePrivate
{
public:
    CSOUND *csound;
    float *csoundBuffer;
    long csoundBufferSize;
    QString deviceName;
    int controlRate;
    int sampleRate;
    int sampleSize;
    int bufferSize;
    int trackCount;
    qreal startTime;
    uint started : sizeof(uint);
    int bytesPerSample;
    AudioSink *sink;
    QAudioFormat::SampleType sampleType;
    QAudioFormat::Endian byteOrder;
    int currentSample;

    CsoundAudioEnginePrivate()
        :   csound(0)
        ,   csoundBuffer(0)
        ,   csoundBufferSize(0)
        ,   controlRate(0)
        ,   sampleRate(0)
        ,   sampleSize(0)
        ,   bufferSize(0)
        ,   trackCount(0)
        ,   startTime(0.0)
        ,   started(false)
        ,   bytesPerSample(0)
        ,   sink(0)
        ,   sampleType(QAudioFormat::SignedInt)
        ,   byteOrder(QAudioFormat::LittleEndian)
        ,   currentSample(0)
    {
        d_instance = this;

        csoundInitialize(0, 0, 0);
        csound = csoundCreate(0);
        if (!csound)
            qDebug() << Q_FUNC_INFO << "Error creating csound";

        const QString opcodeDir = rootDirName();
        const QByteArray opcodeDir_ba = opcodeDir.toLocal8Bit();
        csoundSetGlobalEnv("OPCODEDIR", opcodeDir_ba.constData());

        readSettings();
    }

    ~CsoundAudioEnginePrivate()
    {
        stop();
        if (csound)
            csoundDestroy(csound);
        delete sink;
        writeSettings();
    }

    void readSettings()
    {
        QSettings* settings = Core::ICore::instance()->settings();

        deviceName = settings->value("AudioEngine/DeviceName").toString();
        if (deviceName.isEmpty())
            deviceName = QAudioDeviceInfo::defaultOutputDevice().deviceName();

        QAudioDeviceInfo device_info = Ac::deviceInfo(deviceName);

        sampleRate = settings->value("AudioEngine/SampleRate").toInt();
        if (!sampleRate)
            sampleRate = device_info.preferredFormat().sampleRate();

        sampleSize = settings->value("AudioEngine/SampleSize").toInt();
        if (!sampleSize)
            sampleSize = device_info.preferredFormat().sampleSize();

        controlRate = settings->value("AudioEngine/ControlRate").toInt();
        if (!IAudioEngine::instance()->controlRateIsValid(controlRate, sampleRate))
            controlRate = IAudioEngine::instance()->defaultControlRate(sampleRate);

        bufferSize = settings->value("AudioEngine/BufferSize").toInt();
        if (!bufferSize)
            bufferSize = 2048;

        update();
        writeSettings();
    }

    void writeSettings()
    {
        QSettings* settings = Core::ICore::instance()->settings();
        settings->setValue("AudioEngine/DeviceName", deviceName);
        settings->setValue("AudioEngine/ControlRate", controlRate);
        settings->setValue("AudioEngine/SampleRate", sampleRate);
        settings->setValue("AudioEngine/SampleSize", sampleSize);
        settings->setValue("AudioEngine/BufferSize", bufferSize);
    }

    void update()
    {
        if (!csound)
            return;

        stop();

        csoundBuffer = 0;
        csoundBufferSize = 0;
        bytesPerSample = sampleSize / 8;

        QAudioDeviceInfo device_info = Ac::deviceInfo(deviceName);
        QAudioFormat format;
        format.setChannelCount(2);
        format.setCodec("audio/pcm");
        format.setSampleRate(sampleRate);
        format.setSampleSize(sampleSize);
        format.setSampleType(QAudioFormat::SignedInt);
        delete sink;
        sink = new AudioSink(device_info, format, bufferSize, audioSinkCallback);

        format = sink->format();
        sampleType = format.sampleType();
        byteOrder = format.byteOrder();

        csoundReset(csound);

        if (CSOUND_SUCCESS != csoundPreCompile(csound)) {
            qDebug() << Q_FUNC_INFO << "Error precompiling csound";
            return;
        } else
            csoundSetHostImplementedAudioIO(csound, 1, bufferSize);

        char first_arg[] = "";
        char output_arg[] = "-+rtaudio=null";
        char displays_arg[] = "-d";

        const QString sample_rate = QString("-r%1").arg(sampleRate);
        QByteArray sample_rate_ba = sample_rate.toLocal8Bit();
        char *sample_rate_arg = sample_rate_ba.data();

        const QString control_rate = QString("-k%1").arg(controlRate);
        QByteArray control_rate_ba = control_rate.toLocal8Bit();
        char *control_rate_arg = control_rate_ba.data();

        const QString csd = rootDirName() + "testing/moogladder.csd";
        QByteArray csd_ba = csd.toLocal8Bit();
        char *csd_arg = csd_ba.data();

        const int argc = 6;
        char *argv[] = { first_arg, output_arg, displays_arg, sample_rate_arg, control_rate_arg, csd_arg };
        for (int i = 0;  i < argc;  ++i)
            qDebug() << Q_FUNC_INFO << "arg" << i << "==" << argv[i];
        if (CSOUND_SUCCESS != csoundCompile(csound, argc, argv)) {
            qDebug() << Q_FUNC_INFO << "Error compiling csound";
            return;
        } else {
            csoundBuffer = csoundGetOutputBuffer(csound);
            if (!csoundBuffer) {
                qDebug() << Q_FUNC_INFO << "Error getting csound buffer";
                return;
            }
        }
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
            qDebug() << Q_FUNC_INFO << "Csound buffer size is zero";
            csoundBufferSize = -1;
        }
        if (csoundBufferSize <= 0)
            return byteCount;

        uchar *output_data = reinterpret_cast<uchar*>(data);

        qint64 bytes_read = 0;
        while (bytes_read < byteCount) {
            bool score_done = false;
            if (currentSample == 0)
                score_done = csoundPerformBuffer(csound);

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
                if ((bytes_read + (csoundBufferSize - current_byte)) < byteCount)
                    n = csoundBufferSize - current_byte;
                else
                    n = byteCount - bytes_read;
                currentSample = 0;
            }

            bytes_read += n;

            while (n) {
                const float x = *csound_data;

                if (8 == sampleSize) {
                    if (QAudioFormat::UnSignedInt == sampleType) {
                        const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                        *reinterpret_cast<quint8*>(output_data) = value;
                    } else if (QAudioFormat::SignedInt == sampleType) {
                        const qint8 value = static_cast<qint8>(x * 127);
                        *reinterpret_cast<quint8*>(output_data) = value;
                    }
                } else if (16 == sampleSize) {
                    if (QAudioFormat::UnSignedInt == sampleType) {
                        quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
                        if (QAudioFormat::LittleEndian == byteOrder)
                            qToLittleEndian<quint16>(value, output_data);
                        else
                            qToBigEndian<quint16>(value, output_data);
                    } else if (QAudioFormat::SignedInt == sampleType) {
                        qint16 value = static_cast<qint16>(x * 32767);
                        if (QAudioFormat::LittleEndian == byteOrder)
                            qToLittleEndian<qint16>(value, output_data);
                        else
                            qToBigEndian<qint16>(value, output_data);
                    }
                }

                ++csound_data;
                output_data += bytesPerSample;
                n -= bytesPerSample;
            }

            if (score_done) {
                stop();
                break;
            }
        }

        return byteCount;
    }
};

qint64 audioSinkCallback(char *data, qint64 byteCount)
{
    return d_instance->read(data, byteCount);
}

CsoundAudioEngine::CsoundAudioEngine()
    :   d(new CsoundAudioEnginePrivate)
{}

CsoundAudioEngine::~CsoundAudioEngine()
{
    delete d;
}

bool CsoundAudioEngine::controlRateIsValid(int controlRate, int sampleRate) const
{
    return integerMultiples(sampleRate).contains(controlRate);
}

int CsoundAudioEngine::defaultControlRate(int sampleRate) const
{
    QList<int> control_rates = integerMultiples(sampleRate);
    int control_rate = sampleRate / 10;

    if (!control_rates.contains(control_rate)) {
        const int n = control_rates.count();
        for (int i = 0;  i < n;  ++i) {
            if (control_rate <= control_rates.at(i)) {
                control_rate = control_rates.at(i);
                break;
            }
        }
    }

    if (!control_rates.contains(control_rate))
        control_rate = sampleRate;

    return control_rate;
}

bool CsoundAudioEngine::bufferSizeIsValid(int bufferSize, int controlSamples) const
{
    return 0 == (bufferSize % controlSamples);
}

int CsoundAudioEngine::defaultBufferSize(int controlSamples, int sampleRate) const
{
    QList<int> buffer_sizes = bufferSizes(controlSamples, sampleRate);
    return buffer_sizes.at(buffer_sizes.count() / 2);
}

int CsoundAudioEngine::controlRate() const
{
    return d->controlRate;
}

void CsoundAudioEngine::setControlRate(int rate)
{
    Core::ICore::instance()->settings()->setValue("AudioEngine/ControlRate", rate);
    d->controlRate = rate;
}

int CsoundAudioEngine::sampleRate() const
{
    return d->sampleRate;
}

void CsoundAudioEngine::setSampleRate(int rate)
{
    Core::ICore::instance()->settings()->setValue("AudioEngine/SampleRate", rate);
    d->sampleRate = rate;
}

int CsoundAudioEngine::sampleSize() const
{
    return d->sampleSize;
}

void CsoundAudioEngine::setSampleSize(int size)
{
    Core::ICore::instance()->settings()->setValue("AudioEngine/SampleSize", size);
    d->sampleSize = size;
}

int CsoundAudioEngine::bufferSize() const
{
    return d->bufferSize;
}

void CsoundAudioEngine::setBufferSize(int size)
{
    Core::ICore::instance()->settings()->setValue("AudioEngine/BufferSize", size);
    d->bufferSize = size;
}

const QString &CsoundAudioEngine::deviceName() const
{
    return d->deviceName;
}

void CsoundAudioEngine::setDeviceName(const QString &name)
{
    Core::ICore::instance()->settings()->setValue("AudioEngine/DeviceName", name);
    d->deviceName = name;
}

void CsoundAudioEngine::applySettings()
{
    d->update();
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
