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

#include <ac_audiosink.h>

#include <QAudioOutput>

#include <QDebug>
#include <QIODevice>

class AudioSinkDevice : public QIODevice
{
public:
    int bufferSize;
    AudioSink::Callback *callback;

    AudioSinkDevice(int bufferSize, AudioSink::Callback *callback, QObject *parent = 0)
        :   QIODevice(parent)
        ,   bufferSize(bufferSize)
        ,   callback(callback)
    {
        if (!open(QIODevice::ReadOnly))
            qDebug() << Q_FUNC_INFO << "Error opening audio sink device";
    }

    qint64 readData(char *data, qint64 maxSize)
    {
        return callback(data, maxSize);
    }

    qint64 writeData(const char *data, qint64 maxSize)
    {
        Q_UNUSED(data);
        Q_UNUSED(maxSize);
        return 0;
    }
};

class AudioSinkPrivate
{
public:
    QAudioOutput *output;
    AudioSinkDevice *device;

    AudioSinkPrivate(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, AudioSink::Callback *callback)
        :   output(new QAudioOutput(deviceInfo, format))
        ,   device(new AudioSinkDevice(bufferSize, callback))
    {}

    ~AudioSinkPrivate()
    {
        delete device;
        delete output;
    }
};

AudioSink::AudioSink(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Callback *callback, QObject *parent)
    :   QObject(parent)
    ,   d(new AudioSinkPrivate(deviceInfo, format, bufferSize, callback))
{}

AudioSink::~AudioSink()
{
    stop();
    delete d;
}

QAudioFormat AudioSink::format() const
{
    return d->output->format();
}

void AudioSink::start()
{
    d->device->reset();
    d->output->start(d->device);
}

void AudioSink::stop()
{
    d->output->stop();
}
