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

#include "ac_note.h"

#include <ac_fcurve.h>

using namespace Private;

namespace Private {

class AcNoteData
{
public:
    qreal startTime;
    qreal duration;
    qreal pitchScale;
    qreal volumeScale;
    AcFCurve *pitchCurve;
    AcFCurve *volumeCurve;
    int pitchPointCount;
    int volumePointCount;

    AcNoteData()
        :   startTime(0.0f)
        ,   duration(0.0f)
        ,   pitchScale(1.0f)
        ,   volumeScale(1.0f)
        ,   pitchCurve(0)
        ,   volumeCurve(0)
        ,   pitchPointCount(64)
        ,   volumePointCount(64)
    {}
};

} // namespace Private

AcNote::AcNote(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcNoteData)
{}

AcNote::~AcNote()
{
    delete d;
}

qreal AcNote::startTime() const
{
    return d->startTime;
}

void AcNote::setStartTime(qreal time)
{
    if (time < 0.0f)
        time = 0.0f;
    if (d->startTime == time)
        return;
    d->startTime = time;
    emit propertyChanged(propertyIndex("startTime"));
}

qreal AcNote::duration() const
{
    return d->duration;
}

void AcNote::setDuration(qreal duration)
{
    if (duration < 0.0f)
        duration = 0.0f;
    if (d->duration == duration)
        return;
    d->duration = duration;
    emit propertyChanged(propertyIndex("duration"));
}

qreal AcNote::pitchScale() const
{
    return d->pitchScale;
}

void AcNote::setPitchScale(qreal scale)
{
    if (d->pitchScale == scale)
        return;
    d->pitchScale = scale;
    emit propertyChanged(propertyIndex("pitchScale"));
}

qreal AcNote::volumeScale() const
{
    return d->volumeScale;
}

void AcNote::setVolumeScale(qreal scale)
{
    if (d->volumeScale == scale)
        return;
    d->volumeScale = scale;
    emit propertyChanged(propertyIndex("volumeScale"));
}

AcFCurve *AcNote::pitchCurve() const
{
    return d->pitchCurve;
}

void AcNote::setPitchCurve(AcFCurve *curve)
{
    if (d->pitchCurve == curve)
        return;
    d->pitchCurve = curve;
    emit propertyChanged(propertyIndex("pitchCurve"));
}

AcFCurve *AcNote::volumeCurve() const
{
    return d->volumeCurve;
}

void AcNote::setVolumeCurve(AcFCurve *curve)
{
    if (d->volumeCurve == curve)
        return;
    d->volumeCurve = curve;
    emit propertyChanged(propertyIndex("volumeCurve"));
}

int AcNote::pitchPointCount() const
{
    return d->pitchPointCount;
}

void AcNote::setPitchPointCount(int count)
{
    if (d->pitchPointCount == count)
        return;
    d->pitchPointCount = count;
    emit propertyChanged(propertyIndex("pitchPointCount"));
}

int AcNote::volumePointCount() const
{
    return d->volumePointCount;
}

void AcNote::setVolumePointCount(int count)
{
    if (d->volumePointCount == count)
        return;
    d->volumePointCount = count;
    emit propertyChanged(propertyIndex("volumePointCount"));
}

MiObject *AcNote::pitchCurveObject() const
{
    return d->pitchCurve;
}

void AcNote::setPitchCurveObject(MiObject *curve)
{
    setPitchCurve(qobject_cast<AcFCurve*>(curve));
}

MiObject *AcNote::volumeCurveObject() const
{
    return d->volumeCurve;
}

void AcNote::setVolumeCurveObject(MiObject *curve)
{
    setVolumeCurve(qobject_cast<AcFCurve*>(curve));
}
