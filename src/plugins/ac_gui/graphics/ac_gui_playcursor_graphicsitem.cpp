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

#include "ac_gui_playcursor_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <mi_core_object_aggregate.h>
#include <QGraphicsLineItem>
#include <QPen>

using namespace Ac;
using namespace Qt;

namespace PlayCursor {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   Base::GraphicsItem(aggregate)
    ,   _timeLineNode(0)
    ,   _pitchLineNode(0)
    ,   _controlLineNode(0)
{
    _timeLineNode = new QGraphicsLineItem;
    _pitchLineNode = new QGraphicsLineItem;
    _controlLineNode = new QGraphicsLineItem;
    const QVariant data = quintptr(this);
    _timeLineNode->setData(0, data);
    _pitchLineNode->setData(0, data);
    _controlLineNode->setData(0, data);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(green);
    _timeLineNode->setPen(pen);
    _pitchLineNode->setPen(pen);
    _controlLineNode->setPen(pen);
    update(PlaybackTimeRole, 0.0f);
}

Object::Aggregate *GraphicsItem::aggregate() const
{
    return static_cast<Object::Aggregate*>(Base::GraphicsItem::aggregate());
}

int GraphicsItem::transformType() const
{
    return UnitYTransform;
}

bool GraphicsItem::intersects(const QRectF &rect) const
{
    qreal line_x = _timeLineNode->line().x1();
    if (rect.left() <= line_x && line_x <= rect.right())
        return true;
    return false;
}

IGraphicsItem *GraphicsItem::parent() const
{
    return query<IGraphicsItem>(aggregate()->parent());
}

QGraphicsItem *GraphicsItem::findNode(int sceneType, int transformType) const
{
    if (UnitYTransform != transformType)
        return 0;
    switch (sceneType) {
    case TimeLabelScene:
        return _timeLineNode;
    case PitchScene:
        return _pitchLineNode;
    case ControlScene:
        return _controlLineNode;
    default:
        return 0;
    }
}

void GraphicsItem::update(int role, const QVariant &value)
{
    if (PlaybackTimeRole != role)
        return;
    qreal x = qvariant_cast<qreal>(value);
    _timeLineNode->setLine(x, -1.0f, x, 2.0f);
    _pitchLineNode->setLine(x, -1.0f, x, 2.0f);
    _controlLineNode->setLine(x, -1.0f, x, 2.0f);
}

}
