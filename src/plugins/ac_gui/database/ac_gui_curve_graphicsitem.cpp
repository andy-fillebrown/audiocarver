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
#include "ac_gui_graphicscurvenode.h"
#include <imodeldata.h>
#include <imodelitem.h>
#include <iaggregate.h>

using namespace Ac;

namespace Curve {

void *GraphicsItem::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<GraphicsItem*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *GraphicsItem::initialize()
{
    _curveNode = new GraphicsCurveNode;
    _curveNode->setModelItem(query<IModelItem>(this));
    return aggregate()->append(this);
}

GraphicsItem::~GraphicsItem()
{
    delete _curveNode;
}

void GraphicsItem::setColor(int color)
{
    curveNode()->setColor(color);
}

void GraphicsItem::setPoints(const PointList &points)
{
    curveNode()->setPoints(points);
}

bool GraphicsItem::intersects(const QRectF &rect) const
{
    return curveNode()->intersects(rect);
}

void GraphicsItem::highlight(bool on)
{
    curveNode()->highlight(on);
}

bool GraphicsItem::isVisible() const
{
    return curveNode()->isVisible();
}

void GraphicsItem::update(int role)
{
    switch (role) {
    case PointsRole:
        query<IGraphicsCurve>(this)->setPoints(query<IModelData>(this)->get<PointList>(PointsRole));
    }
}

}
