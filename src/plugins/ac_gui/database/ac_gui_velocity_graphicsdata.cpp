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

#include "ac_gui_velocity_graphicsdata.h"
#include "ac_gui_graphicscurvenode.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <igraphicsitem.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <QPen>

using namespace Ac;

namespace Velocity {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Object::GraphicsCurve(aggregate)
    ,   _lineNode(0)
{
    _lineNode = new QGraphicsLineItem;
    QPen pen;
    pen.setCosmetic(true);
    _lineNode->setPen(pen);
    highlight(false);
}

void GraphicsData::initialize()
{
    IModelItem *this_item = QUERY(IModelItem, this);
    IModelItem *parent_item = this_item->parent();
    IGraphicsData *parent_gdata = QUERY(IGraphicsData, parent_item);
    _lineNode->setParentItem(parent_gdata->node(ControlScene, MainTransform));
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    _lineNode->setData(0, quintptr(this_gitem));
}

QGraphicsItem *GraphicsData::node(int sceneType, int transformType) const
{
    if (ControlScene == sceneType
            && MainTransform == transformType)
        return _lineNode;
    return 0;
}

bool GraphicsData::intersects(const QRectF &rect) const
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

void GraphicsData::highlight(bool on)
{
    QPen pen = _lineNode->pen();
    if (on)
        pen.setWidth(3.0f);
    else
        pen.setWidth(1.0f);
    _lineNode->setPen(pen);
}

void GraphicsData::update(int role, const QVariant &value)
{
    if (VolumeRole == role) {
        IModelItem *this_item = QUERY(IModelItem, this);
        IModelItem *parent_item = this_item->parent();
        if (!parent_item)
            return;
        PointList pitch_points = QUERY(IModelData, parent_item->findItem(PitchCurveItem))->get<PointList>(PointsRole);
        if (pitch_points.isEmpty())
            return;
        qreal x = pitch_points.first().pos.x();
        qreal volume = qvariant_cast<qreal>(value);
        _lineNode->setLine(x, 0.0f, x, volume);
        return;
    }
    if (ColorRole == role) {
        QPen pen = _lineNode->pen();
        pen.setColor(qvariant_cast<int>(value));
        _lineNode->setPen(pen);
        return;
    }
}

}
