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

#include "ac_gui_graphicsgripnode.h"
#include <QPen>

const qreal GRIP_SIZE    = qreal(8.0f);
const qreal GRIP_SIZE_D2 = GRIP_SIZE / qreal(2.0f);
const QRect GRIP_RECT    = QRect(-GRIP_SIZE_D2, -GRIP_SIZE_D2, GRIP_SIZE, GRIP_SIZE);

using namespace Ac;

GraphicsGripNode::GraphicsGripNode(QGraphicsItem *parent, const QPointF &position)
    :   QGraphicsRectItem(parent)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setRect(GRIP_RECT);
    setPos(position);
    highlight(false);
}

void GraphicsGripNode::setModelItem(IModelItem *modelItem)
{
    const QVariant data = quintptr(modelItem);
    setData(0, data);
}

void GraphicsGripNode::highlight(bool on)
{
    QPen pen = this->pen();
    QBrush brush = this->brush();
    if (on) {
        if (brush.style() == Qt::SolidPattern)
            pen.setColor(Qt::red);
        brush.setStyle(Qt::SolidPattern);
    } else {
        if (QColor(Qt::red) == pen.color())
            brush.setStyle(Qt::NoBrush);
        pen.setColor(Qt::blue);
    }
    setBrush(brush);
    setPen(pen);
}
