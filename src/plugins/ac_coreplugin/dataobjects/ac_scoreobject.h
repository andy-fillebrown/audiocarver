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

#ifndef AC_SCOREOBJECT_H
#define AC_SCOREOBJECT_H

#include <ac_core_global.h>
#include <mi_scopedchange.h>

class AcPitchCurve;
class AcVolumeCurve;

class AcScoreObjectPrivate : public MiObjectPrivate
{
public:
    qreal volume;
    quint32 color;
    AcPitchCurve *pitchCurve;
    AcVolumeCurve *volumeCurve;

    AcScoreObjectPrivate(MiObject *q);

    ~AcScoreObjectPrivate()
    {}

    void init();
};

class AC_CORE_EXPORT AcScoreObject : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)
    Q_PROPERTY(quint32 color READ color WRITE setColor)
    Q_PROPERTY(AcPitchCurve* pitchCurve READ pitchCurve)
    Q_PROPERTY(AcVolumeCurve* volumeCurve READ volumeCurve)

public:
    enum PropertyIndex {
        VolumeIndex = MiObject::PropertyCount,
        ColorIndex,
        PitchCurveIndex,
        VolumeCurveIndex,
        PropertyCount
    };

    ~AcScoreObject()
    {}

    qreal volume() const
    {
        Q_D(const AcScoreObject);
        return d->volume;
    }

    void setVolume(qreal volume)
    {
        Q_D(AcScoreObject);
        if (volume < 0.0f)
            volume = 0.0f;
        if (1.0f < volume)
            volume = 1.0f;
        if (volume == d->volume)
            return;
        changing(VolumeIndex);
        d->volume = volume;
    }

    quint32 color() const
    {
        Q_D(const AcScoreObject);
        return d->color;
    }

    void setColor(quint32 color)
    {
        Q_D(AcScoreObject);
        if (color == d->color)
            return;
        changing(ColorIndex);
        d->color = color;
    }

    AcPitchCurve *pitchCurve() const
    {
        Q_D(const AcScoreObject);
        return d->pitchCurve;
    }

    AcVolumeCurve *volumeCurve() const
    {
        Q_D(const AcScoreObject);
        return d->volumeCurve;
    }

protected:
    AcScoreObject(AcScoreObjectPrivate &dd)
        :   MiObject(dd)
    {
        Q_D(AcScoreObject);
        d->init();
    }

private:
    Q_DISABLE_COPY(AcScoreObject)
    Q_DECLARE_PRIVATE(AcScoreObject)
};

#endif // AC_SCOREOBJECT_H
