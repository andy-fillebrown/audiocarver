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

#include "ac_pitchcurve.h"
#include <ac_pitchpoint.h>

AcPitchCurve::AcPitchCurve(int propertyIndex)
:   AcCurve(*(new AcPitchCurvePrivate(this, propertyIndex)))
{
    d_ptr->addChild(new AcPitchPoint);
    d_ptr->addChild(new AcPitchPoint);
}

const QList<AcPitchPoint*> &AcPitchCurve::children() const
{
    return reinterpret_cast<const QList<AcPitchPoint*>&>(QObject::children());
}

void AcPitchCurve::addChild(MiObject *child)
{
    if (!qobject_cast<AcPitchPoint*>(child))
        return;
    MiSortedListObject::addChild(child);
}
