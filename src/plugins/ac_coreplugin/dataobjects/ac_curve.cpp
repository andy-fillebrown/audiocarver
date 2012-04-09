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

#include <mi_scopedchange.h>

Curve::Curve()
    :   _graphicsCurveItem(new GraphicsCurveItem)
{
    static PointList points;
    _pointsStack.push(points);
    graphicsCurveItem()->setEntity(query<IEntity>(this));
}

Curve::~Curve()
{}

bool Curve::setPoints(const PointList &points)
{
    PointList new_pts = points;
    while (1 < _pointsStack.count())
        _pointsStack.pop();
    PointList old_pts = _pointsStack.top();
    _pointsStack.top() = new_pts;
    conformPoints();
    new_pts = _pointsStack.top();
    _pointsStack.top() = old_pts;
    if (_pointsStack.top() == new_pts)
        return false;
    Q_MI_SCOPED_CHANGE(Ac::PointsRole);
    _pointsStack.top() = new_pts;
    updateGraphicsItems();
    return true;
}

void Curve::updateGraphicsItems()
{
    graphicsCurveItem()->setPoints(pointsStack().top());
    scoreObject()->updatePoints();
}

void Curve::setColor(const QColor &color)
{
    graphicsCurveItem()->setColor(color);
}

GraphicsParent *Curve::graphicsParent() const
{
    return scoreObject();
}

void Curve::Entity::highlight()
{
    dataObject()->graphicsCurveItem()->highlight();
}

void Curve::Entity::unhighlight()
{
    dataObject()->graphicsCurveItem()->unhighlight();
}

bool Curve::Entity::intersects(const QRectF &rect) const
{
    return dataObject()->graphicsCurveItem()->intersects(rect);
}

bool Curve::Entity::isVisible() const
{
    return dataObject()->graphicsCurveItem()->isVisible();
}

QVariant Curve::ModelData::get(int role) const
{
    if (Ac::PointsRole == role)
        return QVariant::fromValue(dataObject()->pointsStack().top());
    return GraphicsObject::ModelData::get(role);
}

bool Curve::ModelData::set(const QVariant &data, int role)
{
    if (Ac::PointsRole == role)
        return dataObject()->setPoints(qvariant_cast<PointList>(data));
    return GraphicsObject::ModelData::set(data, role);
}
