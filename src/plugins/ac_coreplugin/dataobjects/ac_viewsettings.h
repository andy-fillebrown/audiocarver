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

#ifndef AC_VIEWSETTINGS_H
#define AC_VIEWSETTINGS_H

#include <mi_object.h>
#include <ac_core_global.h>

namespace Private {

class AcViewSettingsData
{
public:
    qreal timePosition;
    qreal pitchPosition;
    qreal controlPosition;
    qreal timeScale;
    qreal pitchScale;
    qreal controlScale;

    AcViewSettingsData()
        :   timePosition(0.0f)
        ,   pitchPosition(0.0f)
        ,   controlPosition(0.0f)
        ,   timeScale(1.0f)
        ,   pitchScale(1.0f)
        ,   controlScale(100.0f)
    {}
};

} // namespace Private

class AC_CORE_EXPORT AcViewSettings : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AcViewSettings)
    Q_PROPERTY(qreal timePosition READ timePosition WRITE setTimePosition)
    Q_PROPERTY(qreal pitchPosition READ pitchPosition WRITE setPitchPosition)
    Q_PROPERTY(qreal controlPosition READ controlPosition WRITE setControlPosition)
    Q_PROPERTY(qreal timeScale READ timeScale WRITE setTimeScale)
    Q_PROPERTY(qreal pitchScale READ pitchScale WRITE setPitchScale)
    Q_PROPERTY(qreal controlScale READ controlScale WRITE setControlScale)

public:
    enum Properties {
        TimePosition = MiObject::PropertyCount,
        PitchPosition,
        ControlPosition,
        TimeScale,
        PitchScale,
        ControlScale,
        PropertyCount
    };

    AcViewSettings(QObject *parent = 0)
        :   MiObject(parent)
        ,   d(new Private::AcViewSettingsData)
    {}

    ~AcViewSettings()
    {
        delete d;
    }

    qreal timePosition() const
    {
        return d->timePosition;
    }

    void setTimePosition(qreal position)
    {
        if (d->timePosition == position)
            return;
        beginChangeProperty(TimePosition);
        d->timePosition = position;
        endChangeProperty(TimePosition);
    }

    qreal pitchPosition() const
    {
        return d->pitchPosition;
    }

    void setPitchPosition(qreal position)
    {
        if (d->pitchPosition == position)
            return;
        beginChangeProperty(PitchPosition);
        d->pitchPosition = position;
        endChangeProperty(PitchPosition);
    }

    qreal controlPosition() const
    {
        return d->controlPosition;
    }

    void setControlPosition(qreal position)
    {
        if (d->controlPosition == position)
            return;
        beginChangeProperty(ControlPosition);
        d->controlPosition = position;
        endChangeProperty(ControlPosition);
    }

    qreal timeScale() const
    {
        return d->timeScale;
    }

    void setTimeScale(qreal scale)
    {
        if (d->timeScale == scale)
            return;
        beginChangeProperty(TimeScale);
        d->timePosition = scale;
        endChangeProperty(TimeScale);
    }

    qreal pitchScale() const
    {
        return d->pitchScale;
    }

    void setPitchScale(qreal scale)
    {
        if (d->pitchScale == scale)
            return;
        beginChangeProperty(PitchScale);
        d->pitchScale = scale;
        endChangeProperty(PitchScale);
    }

    qreal controlScale() const
    {
        return d->controlScale;
    }

    void setControlScale(qreal scale)
    {
        if (d->controlScale == scale)
            return;
        beginChangeProperty(ControlScale);
        d->controlScale = scale;
        endChangeProperty(ControlScale);
    }

private:
    Private::AcViewSettingsData *d;
};

#endif // AC_VIEWSETTINGS_H
