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

#include "ac_meter.h"

using namespace Private;

namespace Private {

class AcMeterData
{
public:
    AcMeter *q;
    int duration;
    int beatsPerMeasure;
    int denominator;

    AcMeterData(AcMeter *q)
        :  q(q)
        ,   duration(0)
        ,   beatsPerMeasure(4)
        ,   denominator(4)
    {}

    ~AcMeterData()
    {}
};

} // namespace Private

AcMeter::AcMeter(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcMeterData(this))
{}

AcMeter::~AcMeter()
{
    delete d;
}

int AcMeter::duration() const
{
    return d->duration;
}

void AcMeter::setDuration(int duration)
{
    if (duration < 0)
        duration = 0;
    if (d->duration == duration)
        return;
    d->duration = duration;
    emit propertyChanged(propertyIndex("duration"));
}

int AcMeter::beatsPerMeasure() const
{
    return d->beatsPerMeasure;
}

void AcMeter::setBeatsPerMeasure(int beatsPerMeasure)
{
    if (beatsPerMeasure < 1)
        beatsPerMeasure = 1;
    if (d->beatsPerMeasure == beatsPerMeasure)
        return;
    d->beatsPerMeasure = beatsPerMeasure;
    emit propertyChanged(propertyIndex("beatsPerMeasure"));
}

int AcMeter::denominator() const
{
    return d->denominator;
}

void AcMeter::setDenominator(int denominator)
{
    if (denominator < 1)
        denominator = 1;
    if (d->denominator == denominator)
        return;
    d->denominator = denominator;
    emit propertyChanged(propertyIndex("denominator"));
}
