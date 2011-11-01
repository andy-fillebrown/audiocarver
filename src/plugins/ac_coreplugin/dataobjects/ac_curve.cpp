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

#include <ac_scoreobject.h>

CurvePrivate::CurvePrivate(Curve *q)
    :   GraphicsObjectPrivate(q)
    ,   dragging(false)
    ,   graphicsCurveItem(new GraphicsCurveItem)
{}

void CurvePrivate::init()
{
    Q_Q(Curve);
    graphicsCurveItem->setEntity(q);
}

CurvePrivate::~CurvePrivate()
{
    delete graphicsCurveItem;
}

GraphicsParentPrivate *CurvePrivate::graphicsParent() const
{
    Q_Q(const Curve);
    ScoreObject *scoreObject = q->scoreObject();
    return scoreObject ? scoreObject->d_func() : 0;
}

Curve::Curve(CurvePrivate &dd, QObject *parent)
    :   GraphicsObject(dd, parent)
{
    dd.init();
}

void Curve::setColor(const QColor &color)
{
    Q_D(Curve);
    d->graphicsCurveItem->setColor(color);
}

const PointList &Curve::points() const
{
    Q_D(const Curve);
    return d->points;
}

void Curve::setPoints(const PointList &points, Ac::DragState dragState)
{
    Q_D(Curve);
    if (d->points == points) {
        if (Ac::NotDragging == dragState && d->dragging) {
            d->endChangeData();
            d->dragging = false;
        }
        return;
    }
    PointList oldPts = d->points;
    d->points = points;
    d->conformPoints();
    if (d->points == oldPts) {
        if (Ac::NotDragging == dragState && d->dragging) {
            d->endChangeData();
            d->dragging = false;
        }
        return;
    }
    PointList newPts = d->points;
    d->points = oldPts;
    if (Ac::NotDragging == dragState || !d->dragging)
        d->beginChangeData();
    if (Ac::Dragging == dragState)
        d->dragging = true;
    d->points = newPts;
    d->graphicsCurveItem->setPoints(d->points);
    if (!d->dragging)
        d->endChangeData();
    if (Ac::NotDragging == dragState)
        d->dragging = false;
}

void Curve::highlight()
{
    Q_D(Curve);
    d->graphicsCurveItem->highlight();
}

void Curve::unhighlight()
{
    Q_D(Curve);
    d->graphicsCurveItem->unhighlight();
}

bool Curve::intersects(const QRectF &rect) const
{
    Q_D(const Curve);
    return d->graphicsCurveItem->intersects(rect);
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
