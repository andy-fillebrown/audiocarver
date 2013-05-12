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
using namespace Qt;

GraphicsGripNode::GraphicsGripNode(QGraphicsItem *parent, const QPointF &position)
    :   QGraphicsRectItem(parent)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setRect(GRIP_RECT);
    setPos(position);
    QPen pen = this->pen();
    pen.setCosmetic(true);
    pen.setWidth(2);
    pen.setCapStyle(SquareCap);
    pen.setJoinStyle(MiterJoin);
    setPen(pen);
    highlight(NoHighlight);
}

void GraphicsGripNode::setModelItem(IModelItem *modelItem)
{
    const QVariant data = quintptr(modelItem);
    setData(0, data);
}

int GraphicsGripNode::highlightType() const
{
    const QBrush brush = this->brush();
    if (SolidPattern == brush.style()) {
        if (QColor(Qt::blue) == brush.color())
            return HoverHighlight;
        else
            return FullHighlight;
    }
    return NoHighlight;
}

void GraphicsGripNode::highlight(int highlightType)
{
    QPen pen = this->pen();
    QBrush brush = this->brush();
    switch (highlightType) {
    case NoHighlight:
        pen.setColor(Qt::blue);
        brush.setStyle(NoBrush);
        break;
    case HoverHighlight:
        pen.setColor(Qt::blue);
        brush.setColor(Qt::blue);
        brush.setStyle(SolidPattern);
        break;
    case FullHighlight:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        brush.setStyle(SolidPattern);
        break;
    }
    setBrush(brush);
    setPen(pen);
}
