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

int CsoundAudioEngine::controlRate() const
{
    return 0;
}

void CsoundAudioEngine::setControlRate(int rate)
{
    Q_UNUSED(rate);
    qDebug() << Q_FUNC_INFO;
}

int CsoundAudioEngine::sampleRate() const
{
    return 0;
}

void CsoundAudioEngine::setSampleRate(int rate)
{
    Q_UNUSED(rate);
    qDebug() << Q_FUNC_INFO;
}

int CsoundAudioEngine::bitDepth() const
{
    return 0;
}

void CsoundAudioEngine::setBitDepth(int depth)
{
    Q_UNUSED(depth);
    qDebug() << Q_FUNC_INFO;
}

int CsoundAudioEngine::bufferSize() const
{
    return 0;
}

void CsoundAudioEngine::setBufferSize(int size)
{
    Q_UNUSED(size);
    qDebug() << Q_FUNC_INFO;
}

const QString &CsoundAudioEngine::deviceName() const
{
    static QString name;
    return name;
}

void CsoundAudioEngine::setDeviceName(const QString &name)
{
    Q_UNUSED(name);
    qDebug() << Q_FUNC_INFO;
}

bool CsoundAudioEngine::isPlaying() const
{
    return false;
}

void CsoundAudioEngine::play()
{
    qDebug() << Q_FUNC_INFO;
}

void CsoundAudioEngine::stop()
{
    qDebug() << Q_FUNC_INFO;
}

void CsoundAudioEngine::setPlaybackTime(qreal time)
{
    Q_UNUSED(time);
    qDebug() << Q_FUNC_INFO;
}
