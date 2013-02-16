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

#include "ac_gui_velocity_graphicsitem.h"
#include "ac_gui_graphicscurvenode.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <QPen>

using namespace Ac;

namespace Velocity {

void *GraphicsItem::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<GraphicsItem*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *GraphicsItem::initialize()
{
    _lineNode = new QGraphicsLineItem;
    _lineNode->setData(0, quintptr(this));
    IGraphicsItem *parent_graphics = query<IGraphicsItem>(parent());
    QGraphicsItem *parent_node = parent_graphics ? parent_graphics->node(ControlScene, MainTransform) : 0;
    _lineNode->setParentItem(parent_node);
    _lineNode->setData(0, quintptr(this));
    QPen pen;
    pen.setCosmetic(true);
    _lineNode->setPen(pen);
    highlight(false);
    return aggregate()->append(this);
}

GraphicsItem::~GraphicsItem()
{
    delete _lineNode;
}

QGraphicsItem *GraphicsItem::node(int sceneType, int transformType) const
{
    if (ControlScene == sceneType
            && MainTransform == transformType)
        return _lineNode;
    return 0;
}

void GraphicsItem::setColor(int color)
{
    QPen pen = _lineNode->pen();
    pen.setColor(color);
    _lineNode->setPen(pen);
}

void GraphicsItem::setPoints(const PointList &points)
{
    QPointF start_point = points.first().pos;
    QPointF end_point = points.last().pos;
    _lineNode->setLine(start_point.x(), start_point.y(), end_point.x(), end_point.y());
}

bool GraphicsItem::intersects(const QRectF &rect) const
{
    QLineF line = _lineNode->line();
    if (rect.contains(line.p1()) && rect.contains(line.p2()))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topLeft(), rect.topRight()), 0))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topRight(), rect.bottomRight()), 0))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomRight(), rect.bottomLeft()), 0))
        return true;
    if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomLeft(), rect.topLeft()), 0))
        return true;
    return false;
}

void GraphicsItem::highlight(bool on)
{
    QPen pen = _lineNode->pen();
    if (on)
        pen.setWidth(3.0f);
    else
        pen.setWidth(1.0f);
    _lineNode->setPen(pen);
}

bool GraphicsItem::isVisible() const
{
    return _lineNode->isVisible();
}

void GraphicsItem::update(int role)
{
    if (VolumeRole == role) {
        IModelItem *parent_item = parent();
        if (!parent_item)
            return;
        PointList pitch_points = query<IModelData>(parent_item->findItem(PitchCurveItem))->get<PointList>(PointsRole);
        if (pitch_points.isEmpty())
            return;
        qreal volume = query<IModelData>(parent_item)->get<qreal>(VolumeRole);
        PointList velocity_line_points;
        qreal x = pitch_points.first().pos.x();
        velocity_line_points.append(Point(x, 0.0f));
        velocity_line_points.append(Point(x, volume));
        setPoints(velocity_line_points);
    }
}

IModelItem *GraphicsItem::parent() const
{
    return query<IModelItem>(this)->parent();
}

}
