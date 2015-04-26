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
#include "ac_core_namespace.h"
#include "ac_core_point.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace ControlCurve {

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

int ModelItem::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return ControlTypeRole;
    default:
        return Curve::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case ControlTypeRole:
        return QVariant::fromValue(_controlType);
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case ControlTypeRole: {
        int control_type = qvariant_cast<int>(value);
        if (control_type <= 0)
            return false;
        if (_controlType == control_type)
            return false;
        ScopedDataChange data_change(this, ControlTypeRole);
        _controlType = control_type;
        return true;
    }
    default:
        return Curve::ModelItem::setValue(role, value);
    }
}

void ModelItem::conformPoints()
{
    PointList &points = this->points();
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

}
