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

#include "ac_scoreobject.h"
#include <ac_pitchcurve.h>
#include <ac_volumecurve.h>

void AcScoreObject::setPitchCurve(AcPitchCurve *pitchCurve)
{
    Q_D(AcScoreObject);
    if (pitchCurve == d->pitchCurve)
        return;
    emit aboutToChange(PitchCurveIndex, QVariant::fromValue(d->pitchCurve));
    d->removeChild(d->pitchCurve);
    d->pitchCurve = pitchCurve;
    d->addChild(d->pitchCurve);
    emit changed(PitchCurveIndex, QVariant::fromValue(d->pitchCurve));
}

void AcScoreObject::setVolumeCurve(AcVolumeCurve *volumeCurve)
{
    Q_D(AcScoreObject);
    if (volumeCurve == d->volumeCurve)
        return;
    emit aboutToChange(VolumeCurveIndex, QVariant::fromValue(d->volumeCurve));
    d->removeChild(d->volumeCurve);
    d->volumeCurve = volumeCurve;
    d->addChild(d->volumeCurve);
    emit changed(VolumeCurveIndex, QVariant::fromValue(d->volumeCurve));
}
