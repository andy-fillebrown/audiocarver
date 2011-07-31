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

#include "ac_volumecurve.h"
#include <ac_volumepoint.h>

AcVolumeCurve::AcVolumeCurve(int propertyIndex)
    :   AcCurve(*(new AcVolumeCurvePrivate(this, propertyIndex)))
{
    Q_D(AcVolumeCurve);
    d->addChild(new AcVolumePoint);
    d->addChild(new AcVolumePoint);
}

const QList<AcVolumePoint*> &AcVolumeCurve::children() const
{
    return reinterpret_cast<const QList<AcVolumePoint*>&>(QObject::children());
}

void AcVolumeCurve::addChild(MiObject *child)
{
    if (!child->cast<AcVolumePoint>())
        return;
    MiSortedListObject::addChild(child);
}
