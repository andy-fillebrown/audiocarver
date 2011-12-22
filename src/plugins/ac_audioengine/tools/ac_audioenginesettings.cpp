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

#include <QAudioDeviceInfo>

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

void AudioEngineSettings::read(QSettings *settings) const
{
    Q_UNUSED(settings);
}

void AudioEngineSettings::write(QSettings *settings) const
{
    Q_UNUSED(settings);
}

const QString &AudioEngineSettings::deviceName() const
{
    return d->deviceName;
}

void AudioEngineSettings::setDeviceName(const QString &name)
{
    if (name != deviceName())
        d->deviceName = name;
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
    if (rate != sampleRate())
        d->sampleRate = rate;
}

int AudioEngineSettings::controlRate() const
{
    return d->controlRate;
}

void AudioEngineSettings::setControlRate(int rate)
{
    if (rate != controlRate())
        d->controlRate = rate;
}

int AudioEngineSettings::bufferSize() const
{
    return d->bufferSize;
}

void AudioEngineSettings::setBufferSize(int size)
{
    if (size != bufferSize())
        d->bufferSize = size;
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
