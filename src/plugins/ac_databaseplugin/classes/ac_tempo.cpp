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

#include "ac_tempo.h"

using namespace Private;

namespace Private {

class AcTempoData
{
public:
    AcTempo *q;
    qreal startTime;
    qreal beatsPerMinute;

    AcTempoData(AcTempo *q)
        :   q(q)
        ,   startTime(0.0f)
        ,   beatsPerMinute(120.0f)
    {}

    ~AcTempoData()
    {}
};

} // namespace Private

AcTempo::AcTempo(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcTempoData(this))
{}

AcTempo::~AcTempo()
{
    delete d;
}

qreal AcTempo::startTime() const
{
    return d->startTime;
}

void AcTempo::setStartTime(qreal startTime)
{
    if (startTime < 0.0f)
        startTime = 0.0f;
    if (d->startTime == startTime)
        return;
    d->startTime = startTime;
    emit propertyChanged(propertyIndex("startTime"));
}

qreal AcTempo::beatsPerMinute() const
{
    return d->beatsPerMinute;
}

void AcTempo::setBeatsPerMinute(qreal beatsPerMinute)
{
    if (beatsPerMinute < 1.0f)
        beatsPerMinute = 1.0f;
    if (d->beatsPerMinute == beatsPerMinute)
        return;
    d->beatsPerMinute = beatsPerMinute;
    emit propertyChanged(propertyIndex("beatsPerMinute"));
}
