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

#include "accurve.h"

#include <acscoreobject.h>

CurvePrivate::CurvePrivate(Curve *q)
    :   ObjectPrivate(q)
    ,   graphicsCurveItem(new GraphicsCurveItem)
{}

CurvePrivate::~CurvePrivate()
{
    delete graphicsCurveItem;
}

Curve::Curve(CurvePrivate &dd, QObject *parent)
    :   Object(dd, parent)
{}

const PointList &Curve::points() const
{
    Q_D(const Curve);
    return d->points;
}

void Curve::setPoints(const PointList &points)
{
    Q_D(Curve);
    if (d->points == points)
        return;
    PointList oldPts = d->points;
    d->points = points;
    d->conformPoints();
    if (d->points == oldPts)
        return;
    PointList newPts = d->points;
    d->points = oldPts;
    d->beginChangeData();
    d->points = newPts;
    d->graphicsCurveItem->setPoints(d->points);
    d->endChangeData();
}

void Curve::setParent(Object *parent)
{
    Q_D(Curve);
    Object::setParent(parent);
    d->updateGraphicsParent();
}

QVariant Curve::data(int role) const
{
    switch (role) {
    case Ac::PointsRole:
        return QVariant::fromValue(points());
    default:
        return Object::data(role);
    }
}

bool Curve::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::PointsRole:
        setPoints(value.value<PointList>());
        return true;
    default:
        return Object::setData(value, role);
    }
}
