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

#include "ac_core_controlcurve_modelitem.h"
#include "ac_core_curve_aggregate.h"
#include "ac_core_namespace.h"
#include "ac_core_point.h"

using namespace Ac;

namespace ControlCurve {

void ModelItem::conformPoints()
{
    PointList &points = aggregate()->points;
    qSort(points);
    const int n = points.count();
    if (2 <= n) {
        points.first().pos = QPointF();
        points.last().pos.rx() = 1.0f;
        for (int i = 0;  i < n;  ++i) {
            Point &point = points[i];
            point.pos.rx() = qBound(qreal(0.0f), point.pos.x(), qreal(1.0f));
            point.pos.ry() = qBound(qreal(0.0f), point.pos.y(), qreal(1.0f));
        }
    }
}

int ModelItem::itemType() const
{
    return ControlCurveItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (ControlCurveItem == itemType)
        return true;
    return Curve::ModelItem::isTypeOfItem(itemType);
}

}
