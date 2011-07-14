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

#include "ac_point.h"
#include <mi_list.h>

using namespace Private;

namespace Private {

class AcPointData
{
public:
    qreal x;
    qreal y;
    bool curved;

    AcPointData()
        :   x(0.0f)
        ,   y(0.0f)
        ,   curved(false)
    {}
};

} // namespace Private

template <> bool MiList<AcPoint>::lessThan(MiObject *a, MiObject *b)
{
    AcPoint *A = static_cast<AcPoint*>(a);
    AcPoint *B = static_cast<AcPoint*>(b);
    if (A->x() < B->x())
        return true;
    if (A->x() == B->x() && A->y() < B->y())
        return true;
    return false;
}

AcPoint::AcPoint(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcPointData)
{}

AcPoint::~AcPoint()
{
    delete d;
}

qreal AcPoint::x() const
{
    return d->x;
}

void AcPoint::setX(qreal x)
{
    if (d->x == x)
        return;
    d->x = x;
    emit propertyChanged(X);
}

qreal AcPoint::y() const
{
    return d->y;
}

void AcPoint::setY(qreal y)
{
    if (d->y == y)
        return;
    d->y = y;
    emit propertyChanged(Y);
}

bool AcPoint::isCurved() const
{
    return d->curved;
}

void AcPoint::setCurved(bool curved)
{
    if (d->curved == curved)
        return;
    d->curved = curved;
    emit propertyChanged(Curved);
}
