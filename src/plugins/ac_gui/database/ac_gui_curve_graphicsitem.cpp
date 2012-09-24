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

#include "ac_gui_curve_graphicsitem.h"
#include "ac_gui_graphicscurveitem.h"
#include <ientity.h>

using namespace Ac;

namespace Curve {

GraphicsItem::~GraphicsItem()
{
    delete _graphicsCurveItem;
}

IUnknown *GraphicsItem::initialize()
{
    _graphicsCurveItem = new GraphicsCurveItem;
    _graphicsCurveItem->setEntity(query<IEntity>(this));
    return Object::GraphicsItem::initialize();
}

void GraphicsItem::setColor(int color)
{
    _graphicsCurveItem->setColor(color);
}

void GraphicsItem::setPoints(const PointList &points)
{
    _graphicsCurveItem->setPoints(points);
}

bool GraphicsItem::intersects(const QRectF &rect) const
{
    return graphicsCurveItem()->intersects(rect);
}

void GraphicsItem::highlight()
{
    _graphicsCurveItem->highlight();
}

void GraphicsItem::unhighlight()
{
    _graphicsCurveItem->unhighlight();
}

bool GraphicsItem::isVisible() const
{
    return _graphicsCurveItem->isVisible();
}

}
