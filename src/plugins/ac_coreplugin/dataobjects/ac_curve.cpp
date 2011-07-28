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

#include "ac_curve.h"
#include <ac_curvepoint.h>

static bool lessThan(const AcPoint *a, const AcPoint *b)
{
    return a->isLessThan(b);
}

const QList<AcCurvePoint*> &AcCurve::items() const
{
    Q_D(const AcCurve);
    return reinterpret_cast<const QList<AcCurvePoint*>&>(d->children());
}

bool AcCurve::isSorted() const
{
    const QList<AcCurvePoint*> &items = this->items();
    for (int i = 1;  i < items.count();  ++i)
        if (items[i]->isLessThan(items[i - 1]))
            return false;
    return true;
}

void AcCurve::sort()
{
    if (isSorted())
        return;
    Q_D(AcCurve);
    qSort(d->items<AcCurvePoint>(), lessThan);
}

void AcCurve::addItem(MiObject *item)
{
    if (!qobject_cast<AcCurvePoint*>(item))
        return;
    MiSortedListObject::addItem(item);
}

void AcCurve::update()
{
    if (MiObject::ListItemChanged & changedFlags()) {
        // TODO
    }
    MiSortedListObject::update();
}
