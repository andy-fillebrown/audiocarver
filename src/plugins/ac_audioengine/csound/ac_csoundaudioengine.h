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

#ifndef AC_CSOUNDAUDIOENGINE_H
#define AC_CSOUNDAUDIOENGINE_H

#include <ac_iaudioengine.h>

class CsoundAudioEnginePrivate;

class CsoundAudioEngine : public IAudioEngine
{
    Q_OBJECT

public:
    CsoundAudioEngine();
    ~CsoundAudioEngine();

    bool controlRateIsValid(int controlRate, int sampleRate) const;
    int defaultControlRate(int sampleRate) const;

    int controlRate() const;
    void setControlRate(int rate);

    int sampleRate() const;
    void setSampleRate(int rate);

    int sampleSize() const;
    void setSampleSize(int size);

    int bufferSize() const;
    void setBufferSize(int size);

    const QString &deviceName() const;
    void setDeviceName(const QString &name);

    int trackCount() const;
    void setTrackCount(int count);

    qreal startTime() const;
    void setStartTime(qreal time);

    bool isStarted() const;
    void start();
    void stop();

private:
    CsoundAudioEnginePrivate *d;
};

#endif // AC_CSOUNDAUDIOENGINE_H
