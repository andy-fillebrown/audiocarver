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

#include <ac_audiosink.h>

#include <ac_iaudioengine.h>
#include <ac_namespace.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <QAudioOutput>

#include <QIODevice>
#include <QThread>

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

class PlaybackThreadPrivate : public PlaybackThread
{
public:
    QAudioDeviceInfo deviceInfo;
    QAudioFormat format;
    AudioSinkDevice *device;
    QAudioOutput *output;
    uint stopped : bitsizeof(uint);

    PlaybackThreadPrivate()
        :   device(0)
        ,   output(0)
        ,   stopped(true)
    {}

    void start(QAudioDeviceInfo &deviceInfo, QAudioFormat format, AudioSinkDevice *device)
    {
        this->deviceInfo = deviceInfo;
        this->format = format;
        this->device = device;
        QThread::start(QThread::TimeCriticalPriority);
    }

    void stop()
    {
        quit();
        while (!stopped)
            QThread::yieldCurrentThread();
    }

private:
    void run()
    {
        stopped = false;
        QAudioOutput audio_output(deviceInfo, format);
        output = &audio_output;
        output->setNotifyInterval(10);
        connect(output, SIGNAL(notify()), SLOT(notify()), Qt::QueuedConnection);
        output->start(device);
        exec();
        output->stop();
        output = 0;
        stopped = true;
    }

    void notify()
    {
        if (!output)
            return;

        // For some reason, the elapsed micro seconds is only half the actual
        // elapsed micro seconds.  Divide by 500000 instead of 1000000 to make up
        // for it.
        IModel::instance()->rootItem()->setData(output->elapsedUSecs() / 500000.0f, Ac::PlaybackTimeRole);
    }
};

class AudioSinkPrivate
{
public:
    QAudioDeviceInfo deviceInfo;
    QAudioFormat format;
    AudioSinkDevice *device;
    PlaybackThreadPrivate *playbackThread;

    AudioSinkPrivate(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, AudioSink::Callback *callback)
        :   deviceInfo(deviceInfo)
        ,   format(format)
        ,   device(new AudioSinkDevice(bufferSize, callback))
        ,   playbackThread(new PlaybackThreadPrivate)
    {}

    ~AudioSinkPrivate()
    {
        delete playbackThread;
        delete device;
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
    return d->format;
}

void AudioSink::start()
{
    d->device->reset();
    d->playbackThread->start(d->deviceInfo, d->format, d->device);
}

void AudioSink::stop()
{
    IModel::instance()->rootItem()->setData(0.0f, Ac::PlaybackTimeRole);
    d->playbackThread->stop();
}
