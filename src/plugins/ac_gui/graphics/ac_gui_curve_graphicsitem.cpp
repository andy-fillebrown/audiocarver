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

#include "ac_gui_curve_graphicsitem.h"
#include "ac_gui_graphicscurvenode.h"
#include "ac_gui_namespace.h"

using namespace Ac;

namespace Curve {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   Base::GraphicsItem(aggregate)
    ,   _curveNode(0)
{
    _curveNode = new GraphicsCurveNode;
    _curveNode->setGraphicsItem(this);
}

GraphicsItem::~GraphicsItem()
{
    qDelete(_curveNode);
}

int GraphicsItem::transformType() const
{
    return MainTransform;
}

bool GraphicsItem::intersects(const QRectF &rect) const
{
    return _curveNode->intersects(rect);
}

QGraphicsItem *GraphicsItem::findNode(int sceneType, int transformType) const
{
    Q_ASSERT(UnspecifiedScene == sceneType);
    Q_ASSERT(UnspecifiedTransform == transformType);
    return _curveNode;
}

void GraphicsItem::update(int role, const QVariant &value)
{
    QVariant actual_value = value;
    switch (role) {
    case ColorRole:
        _curveNode->setColor(qvariant_cast<QColor>(value));
        break;
    case PointsRole: {
        PointList points = qvariant_cast<PointList>(value);
        const int point_count = points.count();
        for (int i = 0;  i < point_count;  ++i) {
            Point &point = points[i];
            point.pos.rx() = qMax(qreal(0.0f), point.pos.rx());
        }
        actual_value = QVariant::fromValue(points);
        _curveNode->setPoints(qvariant_cast<PointList>(actual_value));
    }   break;
    case HighlightRole:
        _curveNode->highlight(qvariant_cast<bool>(value));
        break;
    }
}

}
