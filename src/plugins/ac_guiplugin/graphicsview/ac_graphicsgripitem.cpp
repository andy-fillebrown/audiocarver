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
    QGraphicsRectItem *item;

    GraphicsGripItemPrivate(GraphicsGripItem *q)
        :   item(new QGraphicsRectItem(q))
    {
        item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        item->setRect(GRIP_RECT);
        item->setData(0, quintptr(query<IGripItem>(q)));

        QPen pen(Qt::blue, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
        item->setPen(pen);
    }

    ~GraphicsGripItemPrivate()
    {
        delete item;
    }

    void setItemColor(const QColor &color)
    {
        QPen pen = item->pen();
        QBrush brush = item->brush();

        pen.setColor(color);
        brush.setColor(color);

        item->setPen(pen);
        item->setBrush(brush);
    }

    void setItemFilled(bool filled)
    {
        QBrush brush = item->brush();

        if (filled)
            brush.setStyle(Qt::SolidPattern);
        else
            brush.setStyle(Qt::NoBrush);

        item->setBrush(brush);
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

IEntityItem *GraphicsGripItem::parentEntityItem() const
{
    return objectToInterface_cast<IEntityItem>(parentItem());
}

const QPointF &GraphicsGripItem::originalPosition() const
{
    return d->originalPos;
}

void GraphicsGripItem::updateOriginalPosition()
{
    d->originalPos = pos();
}

QPointF GraphicsGripItem::position() const
{
    return pos();
}

void GraphicsGripItem::setPosition(const QPointF &position)
{
    setPos(position);
}

void GraphicsGripItem::highlight(HighlightType type)
{
    QPen pen = d->item->pen();
    QBrush brush = d->item->brush();

    switch (type) {
    case HoverHighlight:
        d->setItemColor(Qt::blue);
        break;
    case FullHighlight:
        d->setItemColor(Qt::red);
        break;
    }

    d->setItemFilled(true);
}

void GraphicsGripItem::unhighlight()
{
    d->setItemColor(Qt::blue);
    d->setItemFilled(false);
}
