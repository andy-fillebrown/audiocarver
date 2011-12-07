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

#include <csound.h>

class CsoundAudioEnginePrivate
{
public:
    QString deviceName;
    int controlRate;
    int sampleRate;
    int sampleSize;
    int bufferSize;
    qreal startTime;
    uint started : sizeof(uint);

    CsoundAudioEnginePrivate()
        :   controlRate(0)
        ,   sampleRate(0)
        ,   sampleSize(0)
        ,   bufferSize(0)
        ,   startTime(0.0)
        ,   started(false)
    {}
};

CsoundAudioEngine::CsoundAudioEngine()
    :   d(new CsoundAudioEnginePrivate)
{}

CsoundAudioEngine::~CsoundAudioEngine()
{
    delete d;
}

int CsoundAudioEngine::controlRate() const
{
    return d->controlRate;
}

void CsoundAudioEngine::setControlRate(int rate)
{
    d->controlRate = rate;
}

int CsoundAudioEngine::sampleRate() const
{
    return d->sampleRate;
}

void CsoundAudioEngine::setSampleRate(int rate)
{
    d->sampleRate = rate;
}

int CsoundAudioEngine::sampleSize() const
{
    return d->sampleSize;
}

void CsoundAudioEngine::setSampleSize(int size)
{
    d->sampleSize = size;
}

int CsoundAudioEngine::bufferSize() const
{
    return d->bufferSize;
}

void CsoundAudioEngine::setBufferSize(int size)
{
    d->bufferSize = size;
}

const QString &CsoundAudioEngine::deviceName() const
{
    return d->deviceName;
}

void CsoundAudioEngine::setDeviceName(const QString &name)
{
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
    d->started = uint(true);
}

void CsoundAudioEngine::stop()
{
    d->started = uint(false);
}
