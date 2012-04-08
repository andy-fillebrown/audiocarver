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

#include <ac_graphicsitem.h>
#include <ac_scoreobject.h>

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
    Q_SCOPED_DATA_CHANGE(d, Ac::PointsRole);
    d->pointsStack.top() = new_pts;
    d->graphicsCurveItem()->setPoints(new_pts);
    scoreObject()->updatePoints();
}

void Curve::setColor(const QColor &color)
{
    Q_D(Curve);
    d->graphicsCurveItem()->setColor(color);
}

void CurvePrivate::Entity::highlight()
{
    Q_MI_D(Curve);
    d->graphicsCurveItem()->highlight();
}

void CurvePrivate::Entity::unhighlight()
{
    Q_MI_D(Curve);
    d->graphicsCurveItem()->unhighlight();
}

bool CurvePrivate::Entity::intersects(const QRectF &rect) const
{
    Q_MI_D(const Curve);
    return d->graphicsCurveItem()->intersects(rect);
}

bool CurvePrivate::Entity::isVisible() const
{
    Q_MI_D(const Curve);
    return d->graphicsCurveItem()->isVisible();
}

QVariant CurvePrivate::ModelItem::data(int role) const
{
    if (Ac::PointsRole == role) {
        Q_MI_Q(const Curve);
        return QVariant::fromValue(q->points());
    }
    return GraphicsObjectPrivate::ModelItem::data(role);
}

bool CurvePrivate::ModelItem::setData(const QVariant &data, int role)
{
    if (Ac::PointsRole == role) {
        Q_MI_Q(Curve);
        q->setPoints(data.value<PointList>());
        return true;
    }
    return GraphicsObjectPrivate::ModelItem::setData(data, role);
}

CurvePrivate::CurvePrivate(Curve *q, ModelItem *modelItem, SubEntity *subEntity)
    :   GraphicsObjectPrivate(q, modelItem)
    ,   _graphicsCurveItem(new GraphicsCurveItem)
    ,   _entity(new Entity(q))
    ,   _subEntity(subEntity)
    ,   _points(new Points(q))
{
    PointList pts;
    pointsStack.push(pts);
}

void CurvePrivate::init()
{
    graphicsCurveItem()->setEntity(entity());
}

GraphicsParentPrivate *CurvePrivate::graphicsParent() const
{
    Q_Q(const Curve);
    ScoreObject *scoreObject = q->scoreObject();
    return scoreObject ? scoreObject->d_func() : 0;
}

void CurvePrivate::updateGraphicsItems()
{
    Q_Q(Curve);
    conformPoints();
    graphicsCurveItem()->setPoints(q->points());
}
