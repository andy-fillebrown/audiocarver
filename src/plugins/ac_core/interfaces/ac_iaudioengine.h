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

#ifndef AC_IAUDIOENGINE_H
#define AC_IAUDIOENGINE_H

#include <ac_core_global.h>

#include <QObject>

class AudioEngineSettings;

class AC_CORE_EXPORT IAudioEngine : public QObject
{
    Q_OBJECT

public:
    IAudioEngine();

    static IAudioEngine *instance();

    virtual const AudioEngineSettings &settings() const = 0;
    virtual void setSettings(const AudioEngineSettings &settings) = 0;

    virtual int trackCount() const = 0;
    virtual void setTrackCount(int count) = 0;

    virtual qreal startTime() const = 0;
    virtual void setStartTime(qreal time) = 0;

    virtual bool isStarted() const = 0;

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

signals:
    void settingsChanged();
};

#endif // AC_IAUDIOENGINE_H
