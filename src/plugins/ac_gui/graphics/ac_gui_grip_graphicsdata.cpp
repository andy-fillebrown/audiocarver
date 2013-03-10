/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_gui_grip_graphicsdata.h"
//#include <ac_gripselectionmodel.h>
//#include <ac_gui_graphicsentityitem.h>
#include "ac_gui_constants.h"
#include "ac_gui_graphicsgripnode.h"
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <QGraphicsRectItem>
#include <QPen>
#include <QRect>

const qreal GRIP_SIZE    = qreal(8.0f);
const qreal GRIP_SIZE_D2 = GRIP_SIZE / qreal(2.0f);
const QRect GRIP_RECT    = QRect(-GRIP_SIZE_D2, -GRIP_SIZE_D2, GRIP_SIZE, GRIP_SIZE);

using namespace Ac;

namespace Grip {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Base::GraphicsEntity(aggregate)
    ,   _gripNode(0)
{
    _gripNode = new GraphicsGripNode;
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::blue);
    _gripNode->setPen(pen);
    QBrush brush;
    brush.setStyle(Qt::NoBrush);
    _gripNode->setBrush(brush);
}

GraphicsData::~GraphicsData()
{
    delete _gripNode;
}

void GraphicsData::initialize()
{
    IModelItem *this_item = QUERY(IModelItem, this);
    IModelItem *parent_item = this_item->parent();
    IGraphicsData *parent_gdata = QUERY(IGraphicsData, parent_item);
    _gripNode->setParentItem(parent_gdata->node(ControlScene, MainTransform));
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    _gripNode->setData(0, quintptr(this_gitem));
}

QGraphicsItem *GraphicsData::node(int sceneType, int transformType) const
{
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    IGraphicsData *parent_gdata = QUERY(IGraphicsData, this_gitem->parent());
    if (parent_gdata->node(sceneType, transformType))
        return _gripNode;
    return 0;
}

void GraphicsData::highlight(bool on)
{
    QPen pen = _gripNode->pen();
    QBrush brush = _gripNode->brush();
    if (on) {
        if (QColor(Qt::blue) == pen.color()) {
            if (Qt::SolidPattern == brush.style())
                pen.setColor(Qt::red);
            else
                brush.setStyle(Qt::SolidPattern);
        }
    } else {
        if (Qt::SolidPattern == brush.style()) {
            if (QColor(Qt::red) == pen.color())
                pen.setColor(Qt::blue);
            else
                brush.setStyle(Qt::NoBrush);
        }
    }
    _gripNode->setBrush(brush);
    _gripNode->setPen(pen);
}

}

//class GraphicsGripItemPrivate
//{
//public:
//    QPointF originalPos;
//    int curveType;
//    QGraphicsRectItem *item;

//    GraphicsGripItemPrivate(GraphicsGripItem *q)
//        :   curveType(Ac::NoCurve)
//        ,   item(new QGraphicsRectItem(q))
//    {
//        item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
//        item->setRect(GRIP_RECT);
//        item->setData(0, quintptr(QUERY(IGripItem, q)));

//        QPen pen(Qt::blue, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
//        item->setPen(pen);
//    }

//    ~GraphicsGripItemPrivate()
//    {
//        delete item;
//    }

//    void setItemColor(const QColor &color)
//    {
//        QPen pen = item->pen();
//        QBrush brush = item->brush();

//        pen.setColor(color);
//        brush.setColor(color);

//        item->setPen(pen);
//        item->setBrush(brush);
//    }

//    void setItemFilled(bool filled)
//    {
//        QBrush brush = item->brush();

//        if (filled)
//            brush.setStyle(Qt::SolidPattern);
//        else
//            brush.setStyle(Qt::NoBrush);

//        item->setBrush(brush);
//    }

//    bool isFullyHighlighted() const
//    {
//        return QColor(Qt::red) == item->pen().color();
//    }
//};

//GraphicsGripItem::GraphicsGripItem(const QPointF &position, int curveType)
//    :   d(new GraphicsGripItemPrivate(this))
//{
//    unhighlight();
//    d->originalPos = position;
//    d->curveType = curveType;
//    setPosition(position);
//}

//GraphicsGripItem::~GraphicsGripItem()
//{
//    GripSelectionModel *grip_model = GripSelectionModel::instance();
//    if (grip_model)
//        grip_model->removeGrip(QUERY(IGripItem, this));
//    delete d;
//}

//IEntityItem *GraphicsGripItem::parentEntityItem() const
//{
//    return objectToInterface_cast<IEntityItem>(parentItem());
//}

//const QPointF &GraphicsGripItem::originalPosition() const
//{
//    return d->originalPos;
//}

//void GraphicsGripItem::updateOriginalPosition()
//{
//    d->originalPos = pos();
//}

//QPointF GraphicsGripItem::position() const
//{
//    return pos();
//}

//void GraphicsGripItem::setPosition(const QPointF &position)
//{
//    setPos(position);
//    if (d->isFullyHighlighted())
//        GripSelectionModel::instance()->update();
//}

//int GraphicsGripItem::curveType() const
//{
//    return d->curveType;
//}

//void GraphicsGripItem::setCurveType(int curveType)
//{
//    if (d->curveType == curveType)
//        return;
//    d->curveType = curveType;
//}

//void GraphicsGripItem::highlight(HighlightType type)
//{
//    QPen pen = d->item->pen();
//    QBrush brush = d->item->brush();

//    switch (type) {
//    case HoverHighlight:
//        d->setItemColor(Qt::blue);
//        break;
//    case FullHighlight:
//        d->setItemColor(Qt::red);
//        GripSelectionModel::instance()->appendGrip(QUERY(IGripItem, this));
//        break;
//    }

//    d->setItemFilled(true);
//}

//void GraphicsGripItem::unhighlight()
//{
//    if (d->isFullyHighlighted())
//        GripSelectionModel::instance()->removeGrip(QUERY(IGripItem, this));
//    d->setItemColor(Qt::blue);
//    d->setItemFilled(false);
//}
