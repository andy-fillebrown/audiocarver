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

#include <icore.h>

#include <csound.h>

#include <QAudioDeviceInfo>

#include <QSettings>

class CsoundAudioEnginePrivate
{
public:
    QString deviceName;
    int controlRate;
    int sampleRate;
    int sampleSize;
    int bufferSize;
    int trackCount;
    qreal startTime;
    uint started : sizeof(uint);

    CsoundAudioEnginePrivate()
        :   controlRate(0)
        ,   sampleRate(0)
        ,   sampleSize(0)
        ,   bufferSize(0)
        ,   trackCount(0)
        ,   startTime(0.0)
        ,   started(false)
    {
        readSettings();
    }

    ~CsoundAudioEnginePrivate()
    {
        writeSettings();
    }

    void readSettings()
    {
        QSettings* settings = Core::ICore::instance()->settings();

        deviceName = settings->value("AudioEngine/DeviceName").toString();
        if (deviceName.isEmpty())
            deviceName = QAudioDeviceInfo::defaultOutputDevice().deviceName();

        QAudioDeviceInfo device_info;
        const QList<QAudioDeviceInfo> devs = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        foreach (const QAudioDeviceInfo &dev_info, devs) {
            if (deviceName == dev_info.deviceName()) {
                device_info = dev_info;
                break;
            }
        }

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

    void start()
    {
        started = true;

//        csoundInitialize(0, 0, 0);

//        CSOUND *csound = csoundCreate(0);
//        if (!csound) {
//            qDebug() << Q_FUNC_INFO << "Error creating";
//            return;
//        }

//        QDir rootDir(QCoreApplication::applicationDirPath());
//        rootDir.cdUp();
//        const QString rootDirName = rootDir.absolutePath() + "/";

//        const QString opcodeDir = rootDirName;
//        const QByteArray opcodeDir_ba = opcodeDir.toLocal8Bit();
//        csoundSetGlobalEnv("OPCODEDIR", opcodeDir_ba.constData());

//        if (CSOUND_SUCCESS != csoundPreCompile(csound))
//            qDebug() << Q_FUNC_INFO << "Error precompiling";
//        else {
//            csoundSetHostImplementedAudioIO(csound, 1, 512);

//            char first_arg[] = "";
//            char output_arg[] = "-odac";
//            char displays_arg[] = "-d";

//            const QString csd = rootDirName + "testing/moogladder.csd";
//            QByteArray csd_ba = csd.toLocal8Bit();
//            char *csd_arg = csd_ba.data();
//            qDebug() << Q_FUNC_INFO << csd_arg;

//            char *args[] = { first_arg, output_arg, displays_arg, csd_arg };
//            if (CSOUND_SUCCESS != csoundCompile(csound, sizeof(*args), args))
//                qDebug() << Q_FUNC_INFO << "Error compiling";
//            else {
//                double *samples = csoundGetOutputBuffer(csound);
//                const long n = csoundGetOutputBufferSize(csound);
//                Q_ASSERT(samples && n);

//                while (!csoundPerformBuffer(csound));
//            }
//        }
//        csoundDestroy(csound);
    }

    void stop()
    {
        started = false;
    }
};

CsoundAudioEngine::CsoundAudioEngine()
    :   d(new CsoundAudioEnginePrivate)
{}

CsoundAudioEngine::~CsoundAudioEngine()
{
    delete d;
}

bool CsoundAudioEngine::controlRateIsValid(int controlRate, int sampleRate) const
{
    QList<int> control_rates;
    for (int i = 1;  i <= sampleRate;  ++i) {
        if (0 == sampleRate % i)
            control_rates.append(i);
    }

    return control_rates.contains(controlRate);
}

int CsoundAudioEngine::defaultControlRate(int sampleRate) const
{
    int control_rate = sampleRate / 10;

    QList<int> control_rates;
    for (int i = 1;  i <= sampleRate;  ++i) {
        if (0 == sampleRate % i)
            control_rates.append(i);
    }

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
