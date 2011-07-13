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
#include <ac_point.h>
#include <mi_list.h>
#include <mi_scopedsignalblocker.h>

using namespace Private;

namespace Private {

class AcCurveData
{
public:
    AcCurve *q;
    MiList<AcPoint> points;

    AcCurveData(AcCurve *q)
        :   q(q)
        ,   points(AcCurve::Points, q)
    {}
};

} // namespace Private

AcCurve::AcCurve(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcCurveData(this))
{
    connect(this, SIGNAL(propertyChanged(int)), SLOT(updateCurveProperty(int)));
}

AcCurve::~AcCurve()
{
    delete d;
}

MiList<AcPoint> &AcCurve::points() const
{
    return d->points;
}

MiObject *AcCurve::createObject(const QString &className)
{
    if ("Point" == className)
        return d->points.add();
    return 0;
}

MiObjectList *AcCurve::pointObjects() const
{
    return d->points.objects();
}

void AcCurve::updateCurveProperty(int propertyIndex)
{
    if (Points == propertyIndex) {
        foreach (AcPoint *point, d->points.list())
            connect(point, SIGNAL(propertyChanged(int)), SLOT(updatePointProperty(int)), Qt::UniqueConnection);
        updatePoints();
    }
}

void AcCurve::updatePointProperty(int propertyIndex)
{
    switch (propertyIndex) {
    case AcPoint::X:
    case AcPoint::Y:
        updatePoints();
        break;
    default:
        break;
    }
}

void AcCurve::updatePoints()
{
    MiScopedSignalBlocker blockSignals(this);
    d->points.sort();
}
