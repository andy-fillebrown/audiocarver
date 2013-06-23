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

#include "mi_audioengine_sink.h"
#include <idatabase.h>
#include <imodelitem.h>
#include <QAudioOutput>
#include <QIODevice>
#include <QThread>
#include <QtDebug>

using namespace Qt;

namespace Mi {
namespace AudioEngine {

class SinkDevice : public QIODevice
{
public:
    int bufferSize;
    Sink::Callback *callback;

    SinkDevice(int bufferSize, Sink::Callback *callback, QObject *parent = 0)
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
        return 0;
    }
};

class PlaybackThreadPrivate : public QThread
{
public:
    Sink *sink;
    QAudioDeviceInfo deviceInfo;
    QAudioFormat format;
    SinkDevice *device;
    QAudioOutput *output;
    uint starting : 1;
    uint stopped : 1;

    PlaybackThreadPrivate(Sink *sink)
        :   sink(sink)
        ,   device(0)
        ,   output(0)
        ,   starting(false)
        ,   stopped(true)
    {}

    void start(QAudioDeviceInfo &deviceInfo, QAudioFormat format, SinkDevice *device)
    {
        starting = true;
        this->deviceInfo = deviceInfo;
        this->format = format;
        this->device = device;
        this->format.setChannelCount(1);
        QThread::start(QThread::TimeCriticalPriority);
    }

    void stop()
    {
        if (starting)
            return;
        quit();
        while (!stopped)
            QThread::yieldCurrentThread();
    }

private:
    void run()
    {
        stopped = false;
        output = new QAudioOutput(deviceInfo, format);
        output->setNotifyInterval(10);
        connect(output, SIGNAL(notify()), sink, SLOT(notify()), UniqueConnection);
        output->start(device);
        starting = false;
        exec();
        // Deleting the QAudioOutput object crashes on linux so we leave it as
        // a small memory/resource leak until the audio engine is rewritten.
#ifndef MI_SKIP_AUDIOOUTPUT_DESTRUCTION
        delete output;
#endif
        output = 0;
        stopped = true;
    }
};

class SinkPrivate
{
public:
    Sink *q;
    QAudioDeviceInfo deviceInfo;
    QAudioFormat format;
    SinkDevice *device;
    PlaybackThreadPrivate *playbackThread;

    SinkPrivate(Sink *q, const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Sink::Callback *callback)
        :   q(q)
        ,   deviceInfo(deviceInfo)
        ,   format(format)
        ,   device(new SinkDevice(bufferSize, callback))
        ,   playbackThread(new PlaybackThreadPrivate(q))
    {}

    ~SinkPrivate()
    {
        delete playbackThread;
        delete device;
    }
};

Sink::Sink(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Callback *callback, QObject *parent)
    :   QObject(parent)
    ,   d(new SinkPrivate(this, deviceInfo, format, bufferSize, callback))
{}

Sink::~Sink()
{
    stop();
    delete d;
}

QAudioFormat Sink::format() const
{
    return d->format;
}

qreal Sink::playbackTime() const
{
    if (!d->playbackThread->output)
        return 0.0f;
    return d->playbackThread->output->elapsedUSecs() / 1000000.0f;
}

void Sink::start()
{
    d->device->reset();
    d->playbackThread->start(d->deviceInfo, d->format, d->device);
}

void Sink::stop()
{
    d->playbackThread->stop();
}

}
}
