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

#include <ac_audioenginesettings.h>

#include <ac_audioengineutils.h>

#include <QAudioDeviceInfo>

#include <QSettings>

class AudioEngineSettingsPrivate : public QSharedData
{
public:
    QString deviceName;
    int sampleSize;
    int sampleRate;
    int controlRate;
    int bufferSize;

    AudioEngineSettingsPrivate()
        :   sampleSize(0)
        ,   sampleRate(0)
        ,   controlRate(0)
        ,   bufferSize(0)
    {}

    void read(QSettings *settings)
    {
        deviceName = settings->value("AudioEngine/DeviceName").toString();
        sampleSize = settings->value("AudioEngine/SampleSize").toInt();
        sampleRate = settings->value("AudioEngine/SampleRate").toInt();
        controlRate = settings->value("AudioEngine/ControlRate").toInt();
        bufferSize = settings->value("AudioEngine/BufferSize").toInt();
        update();
    }

    void write(QSettings *settings) const
    {
        settings->setValue("AudioEngine/DeviceName", deviceName);
        settings->setValue("AudioEngine/SampleSize", sampleSize);
        settings->setValue("AudioEngine/SampleRate", sampleRate);
        settings->setValue("AudioEngine/ControlRate", controlRate);
        settings->setValue("AudioEngine/BufferSize", bufferSize);
    }

    void update()
    {
        if (deviceName.isEmpty())
            deviceName = QAudioDeviceInfo::defaultOutputDevice().deviceName();

        QAudioDeviceInfo device_info = Ac::deviceInfo(deviceName);

        if (!sampleSize)
            sampleSize = device_info.preferredFormat().sampleSize();

        if (!sampleRate)
            sampleRate = device_info.preferredFormat().sampleRate();

        if (!controlRate || (sampleRate % controlRate))
            controlRate = Ac::defaultControlRate(sampleRate);

        if (!bufferSize || (bufferSize % (sampleRate / controlRate)))
            bufferSize = Ac::defaultBufferSize(sampleRate, controlRate);
    }
};

AudioEngineSettings::AudioEngineSettings()
    :   d(new AudioEngineSettingsPrivate)
{}

AudioEngineSettings::AudioEngineSettings(const AudioEngineSettings &other)
    :   d(other.d)
{}

AudioEngineSettings &AudioEngineSettings::operator=(const AudioEngineSettings &other)
{
    d = other.d;
    return *this;
}

AudioEngineSettings::~AudioEngineSettings()
{}

void AudioEngineSettings::read(QSettings *settings)
{
    d->read(settings);
}

void AudioEngineSettings::write(QSettings *settings) const
{
    d->write(settings);
}

const QString &AudioEngineSettings::deviceName() const
{
    return d->deviceName;
}

void AudioEngineSettings::setDeviceName(const QString &name)
{
    if (name != deviceName()) {
        d->deviceName = name;
        d->update();
    }
}

int AudioEngineSettings::sampleSize() const
{
    return d->sampleSize;
}

void AudioEngineSettings::setSampleSize(int size)
{
    if (size != sampleSize())
        d->sampleSize = size;
}

int AudioEngineSettings::sampleRate() const
{
    return d->sampleRate;
}

void AudioEngineSettings::setSampleRate(int rate)
{
    if (rate != sampleRate()) {
        d->sampleRate = rate;
        d->update();
    }
}

int AudioEngineSettings::controlRate() const
{
    return d->controlRate;
}

void AudioEngineSettings::setControlRate(int rate)
{
    if (rate != controlRate()) {
        d->controlRate = rate;
        d->update();
    }
}

int AudioEngineSettings::bufferSize() const
{
    return d->bufferSize;
}

void AudioEngineSettings::setBufferSize(int size)
{
    if (size != bufferSize()) {
        d->bufferSize = size;
        d->update();
    }
}

bool AudioEngineSettings::operator==(const AudioEngineSettings &other) const
{
    const AudioEngineSettingsPrivate *other_d = other.d;
    return d->deviceName == other_d->deviceName
            && d->sampleSize == other_d->sampleSize
            && d->sampleRate == other_d->sampleRate
            && d->controlRate == other_d->controlRate
            && d->bufferSize == other_d->bufferSize;
}

bool AudioEngineSettings::operator!=(const AudioEngineSettings &other) const
{
    const AudioEngineSettingsPrivate *other_d = other.d;
    return d->deviceName != other_d->deviceName
            || d->sampleSize != other_d->sampleSize
            || d->sampleRate != other_d->sampleRate
            || d->controlRate != other_d->controlRate
            || d->bufferSize != other_d->bufferSize;
}
