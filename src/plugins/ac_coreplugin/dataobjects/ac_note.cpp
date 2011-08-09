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
#include <ac_pitchcurve.h>
#include <ac_pitchpoint.h>

bool AcNote::isLessThan(const AcNote *other) const
{
    AcPitchCurve *curveA = pitchCurve();
    AcPitchCurve *curveB = other->pitchCurve();
    AcPitchPoint *ptA = curveA->children().first();
    AcPitchPoint *ptB = curveB->children().first();
    if (ptA->isLessThan(ptB))
        return true;
    if (ptA->x() == ptB->x()
            && ptA->y() == ptB->y()
            && curveA->duration() < curveB->duration())
        return true;
    return false;
}
