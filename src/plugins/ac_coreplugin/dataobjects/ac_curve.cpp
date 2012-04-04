/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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
    ,   graphicsCurveItem(new GraphicsCurveItem)
{
    PointList pts;
    pts.append(Point());
    pts.append(Point());
    pointsStack.push(pts);
}

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
    return d->pointsStack.top();
}

void Curve::pushPoints(const PointList &points)
{
    Q_D(Curve);
    d->pointsStack.push(points);
    d->conformPoints();
    d->graphicsCurveItem->setPoints(this->points());
}

void Curve::popPoints()
{
    Q_D(Curve);
    d->pointsStack.pop();
    d->graphicsCurveItem->setPoints(this->points());
}

void Curve::setPoints(const PointList &points)
{
    Q_D(Curve);
    PointList new_pts = points;
    while (1 < d->pointsStack.count())
        d->pointsStack.pop();
    PointList old_pts = this->points();
    d->pointsStack.top() = new_pts;
    d->conformPoints();
    new_pts = d->pointsStack.top();
    d->pointsStack.top() = old_pts;
    if (this->points() == new_pts)
        return;
    d->beginChangeData();
    d->pointsStack.top() = new_pts;
    d->graphicsCurveItem->setPoints(new_pts);
    scoreObject()->updatePoints();
    d->endChangeData();
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

bool Curve::isVisible() const
{
    Q_D(const Curve);
    return d->graphicsCurveItem->isVisible();
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
