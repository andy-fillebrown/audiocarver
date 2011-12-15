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

class AudioSinkPrivate
{
public:
    AudioSink::Callback *callback;
};

AudioSink::AudioSink(QObject *parent)
    :   QObject(parent)
    ,   d(new AudioSinkPrivate)
{}

AudioSink::~AudioSink()
{
    delete d;
}

void AudioSink::init(const QAudioDeviceInfo &deviceInfo, const QAudioFormat &format, int bufferSize, Callback *callback)
{
    Q_UNUSED(deviceInfo);
    Q_UNUSED(format);
    Q_UNUSED(bufferSize);
    Q_UNUSED(callback);
}

void AudioSink::start()
{
}

void AudioSink::stop()
{
}
