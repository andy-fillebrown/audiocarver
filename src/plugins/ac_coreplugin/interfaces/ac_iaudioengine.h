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

#ifndef AC_IAUDIOENGINE_H
#define AC_IAUDIOENGINE_H

#include <ac_global.h>

#include <QObject>

class AC_CORE_EXPORT IAudioEngine : public QObject
{
    Q_OBJECT

public:
    IAudioEngine();

    static IAudioEngine *instance();

    virtual int controlRate() const = 0;
    virtual void setControlRate(int rate) = 0;

    virtual int sampleRate() const = 0;
    virtual void setSampleRate(int rate) = 0;

    virtual int bitDepth() const = 0;
    virtual void setBitDepth(int depth) = 0;

    virtual int bufferSize() const = 0;
    virtual void setBufferSize(int size) = 0;

    virtual const QString &deviceName() const = 0;
    virtual void setDeviceName(const QString &name) = 0;

    virtual bool isPlaying() const = 0;
    virtual void play() = 0;
    virtual void stop() = 0;

    virtual void setPlaybackTime(qreal time) = 0;
};

#endif // AC_IAUDIOENGINE_H
