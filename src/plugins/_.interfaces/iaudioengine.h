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

#ifndef IAUDIOENGINE_H
#define IAUDIOENGINE_H

#include <icomponent.h>
#include <iaggregate.h>
#include <isession.h>

class AudioEngineSettings;

class IAudioEngine : public IComponent
{
public:
    enum { InterfaceType = I::IAudioEngine };

    inline static IAudioEngine *instance()
    {
        return query<IAudioEngine>(ISession::instance());
    }

    virtual const AudioEngineSettings &settings() const = 0;
    virtual void setSettings(const AudioEngineSettings &settings) = 0;
    virtual int trackCount() const = 0;
    virtual void setTrackCount(int count) = 0;
    virtual qreal startTime() const = 0;
    virtual void setStartTime(qreal time) = 0;
    virtual bool isStarted() const = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif
