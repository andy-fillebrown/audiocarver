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

#include <ac_core_global.h>
#include <mi_scopedchange.h>

class AcViewSettingsPrivate : public MiObjectPrivate
{
public:
    qreal timePosition;
    qreal pitchPosition;
    qreal volumePosition;
    qreal timeScale;
    qreal pitchScale;
    qreal volumeScale;

    AcViewSettingsPrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   timePosition(0.0f)
        ,   pitchPosition(0.0f)
        ,   volumePosition(0.0f)
        ,   timeScale(1.0f)
        ,   pitchScale(1.0f)
        ,   volumeScale(100.0f)
    {}

    virtual ~AcViewSettingsPrivate()
    {}
};

class AC_CORE_EXPORT AcViewSettings : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal timePosition READ timePosition WRITE setTimePosition)
    Q_PROPERTY(qreal pitchPosition READ pitchPosition WRITE setPitchPosition)
    Q_PROPERTY(qreal volumePosition READ volumePosition WRITE setVolumePosition)
    Q_PROPERTY(qreal timeScale READ timeScale WRITE setTimeScale)
    Q_PROPERTY(qreal pitchScale READ pitchScale WRITE setPitchScale)
    Q_PROPERTY(qreal volumeScale READ volumeScale WRITE setVolumeScale)

public:
    enum PropertyIndexes {
        TimePositionIndex = MiObject::PropertyCount,
        PitchPositionIndex,
        VolumePositionIndex,
        TimeScaleIndex,
        PitchScaleIndex,
        VolumeScaleIndex,
        PropertyCount
    };

    AcViewSettings()
        :   MiObject(*(new AcViewSettingsPrivate(this)))
    {}

    ~AcViewSettings()
    {}

    qreal timePosition() const
    {
        Q_D(const AcViewSettings);
        return d->timePosition;
    }

    void setTimePosition(qreal position)
    {
        Q_D(AcViewSettings);
        if (d->timePosition == position)
            return;
        changing(TimePositionIndex);
        d->timePosition = position;
    }

    qreal pitchPosition() const
    {
        Q_D(const AcViewSettings);
        return d->pitchPosition;
    }

    void setPitchPosition(qreal position)
    {
        Q_D(AcViewSettings);
        if (d->pitchPosition == position)
            return;
        changing(PitchPositionIndex);
        d->pitchPosition = position;
    }

    qreal volumePosition() const
    {
        Q_D(const AcViewSettings);
        return d->volumePosition;
    }

    void setVolumePosition(qreal position)
    {
        Q_D(AcViewSettings);
        if (d->volumePosition == position)
            return;
        changing(VolumePositionIndex);
        d->volumePosition = position;
    }

    qreal timeScale() const
    {
        Q_D(const AcViewSettings);
        return d->timeScale;
    }

    void setTimeScale(qreal scale)
    {
        Q_D(AcViewSettings);
        if (d->timeScale == scale)
            return;
        changing(TimeScaleIndex);
        d->timePosition = scale;
    }

    qreal pitchScale() const
    {
        Q_D(const AcViewSettings);
        return d->pitchScale;
    }

    void setPitchScale(qreal scale)
    {
        Q_D(AcViewSettings);
        if (d->pitchScale == scale)
            return;
        changing(PitchScaleIndex);
        d->pitchScale = scale;
    }

    qreal volumeScale() const
    {
        Q_D(const AcViewSettings);
        return d->volumeScale;
    }

    void setVolumeScale(qreal scale)
    {
        Q_D(AcViewSettings);
        if (d->volumeScale == scale)
            return;
        changing(VolumeScaleIndex);
        d->volumeScale = scale;
    }

private:
    Q_DISABLE_COPY(AcViewSettings)
    Q_DECLARE_PRIVATE(AcViewSettings)
};

#endif // AC_VIEWSETTINGS_H
