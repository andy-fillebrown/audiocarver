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

#include "ac_graphicsgripitem.h"

#include <ac_graphicsentityitem.h>

class GraphicsGripItemPrivate
{
public:
    QGraphicsRectItem *rectItem;

    GraphicsGripItemPrivate(GraphicsGripItem *q)
        :   rectItem(new QGraphicsRectItem(q))
    {
        rectItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        rectItem->setRect(-3.0f, -3.0f, 6.0f, 6.0f);
        rectItem->setPen(QPen(Qt::blue));
        rectItem->setBrush(QBrush(Qt::blue));
        rectItem->setData(0, quintptr(query<IGripItem>(q)));
    }

    ~GraphicsGripItemPrivate()
    {
        delete rectItem;
    }
};

GraphicsGripItem::GraphicsGripItem(const QPointF &position)
    :   d(new GraphicsGripItemPrivate(this))
{
    setPosition(position);
}

GraphicsGripItem::~GraphicsGripItem()
{
    delete d;
}

IEntityItem *GraphicsGripItem::parentEntityItem() const
{
    return static_cast<GraphicsEntityItem*>(parentItem());
}

void GraphicsGripItem::setPosition(const QPointF &position)
{
    setPos(position);
}