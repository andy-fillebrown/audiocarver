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
#include <ac_guiconstants.h>

const qreal GRIP_SIZE    = qreal(8.0f);
const qreal GRIP_SIZE_D2 = GRIP_SIZE / qreal(2.0f);
const QRect GRIP_RECT    = QRect(-GRIP_SIZE_D2, -GRIP_SIZE_D2, GRIP_SIZE, GRIP_SIZE);

class GraphicsGripItemPrivate
{
public:
    QPointF originalPos;
    QGraphicsRectItem *rectItem;

    GraphicsGripItemPrivate(GraphicsGripItem *q)
        :   rectItem(new QGraphicsRectItem(q))
    {
        rectItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        rectItem->setRect(GRIP_RECT);
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
    unhighlight();
    d->originalPos = position;
    setPosition(position);
}

GraphicsGripItem::~GraphicsGripItem()
{
    delete d;
}

void GraphicsGripItem::updateOriginalPosition()
{
    d->originalPos = pos();
}

IEntityItem *GraphicsGripItem::parentEntityItem() const
{
    return objectToInterface_cast<IEntityItem>(parentItem());
}

const QPointF &GraphicsGripItem::originalPosition() const
{
    return d->originalPos;
}

void GraphicsGripItem::setPosition(const QPointF &position)
{
    setPos(position);
}

void GraphicsGripItem::highlight()
{
    d->rectItem->setPen(QPen(Qt::red));
    d->rectItem->setBrush(QBrush(Qt::red));
}

void GraphicsGripItem::unhighlight()
{
    d->rectItem->setPen(QPen(Qt::blue));
    d->rectItem->setBrush(QBrush(Qt::blue));
}
