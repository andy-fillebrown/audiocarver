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

#include "ac_core_curve_modelitem.h"
#include "ac_core_curve_aggregate.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace Curve {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return CurveItem == itemType;
}

int ModelItem::roleCount() const
{
    return Aggregate::TotalRoleCount;
}

int ModelItem::roleAt(int i) const
{
    switch (i - Aggregate::RoleCountOffset) {
    case 0:
        return PointsRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case PointsRole:
        return QVariant::fromValue(aggregate()->points);
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case PointsRole: {
        Aggregate *aggregate = this->aggregate();
        const PointList points = qvariant_cast<PointList>(value);
        const PointList old_points = aggregate->points;
        aggregate->points = points;
        conformPoints();
        if (aggregate->points == old_points)
            return false;
        const PointList new_points = aggregate->points;
        aggregate->points = old_points;
        ScopedDataChange data_change(this, PointsRole);
        aggregate->points = new_points;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
