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

#include "ac_gui_curve_graphicsdata.h"
#include "ac_gui_graphicscurvenode.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <igraphicsitem.h>
#include <imodeldata.h>
#include <imodelitem.h>

using namespace Ac;

namespace Curve {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Base::GraphicsCurveData(aggregate)
    ,   _curveNode(0)
{
    _curveNode = new GraphicsCurveNode;
}

GraphicsData::~GraphicsData()
{
    delete _curveNode;
}

void GraphicsData::initialize()
{
    _curveNode->setGraphicsItem(QUERY(IGraphicsItem, this));
}

bool GraphicsData::intersects(const QRectF &rect) const
{
    return _curveNode->intersects(rect);
}

QGraphicsItem *GraphicsData::node() const
{
    return _curveNode;
}

void GraphicsData::update(int role, const QVariant &value)
{
    switch (role) {
    case ColorRole:
        _curveNode->setColor(qvariant_cast<QColor>(value));
        break;
    case PointsRole:
        _curveNode->setPoints(qvariant_cast<PointList>(value));
        break;
    case HighlightRole:
        _curveNode->highlight(qvariant_cast<bool>(value));
        break;
    }
}

}
