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

#include "ac_core_gridline_modelitem.h"
#include "ac_core_gridline_aggregate.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>
#include <mi_core_utilities.h>

using namespace Ac;
using namespace Mi;

namespace GridLine {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return GridLineItem == itemType;
}

int ModelItem::roleCount() const
{
    return Aggregate::TotalRoleCount;
}


int ModelItem::roleAt(int i) const
{
    switch (i - Aggregate::RoleCountOffset) {
    case 0:
        return LocationRole;
    case 1:
        return LabelRole;
    case 2:
        return PriorityRole;
    case 3:
        return ColorRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case LocationRole:
        return aggregate()->location;
    case LabelRole:
        return aggregate()->label;
    case PriorityRole:
        return aggregate()->priority;
    case ColorRole:
        return colorFromInt(aggregate()->color);
    case VisibilityRole:
        return aggregate()->visible;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case LocationRole: {
        Aggregate *aggregate = this->aggregate();
        const qreal location = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (aggregate->location == location)
            return false;
        ScopedDataChange data_change(this, LocationRole);
        aggregate->location = location;
        return true;
    }
    case LabelRole: {
        Aggregate *aggregate = this->aggregate();
        const QString label = qvariant_cast<QString>(value);
        if (aggregate->label == label)
            return false;
        ScopedDataChange data_change(this, LabelRole);
        aggregate->label = label;
        return true;
    }
    case PriorityRole: {
        Aggregate *aggregate = this->aggregate();
        const int priority = qMax(0, qvariant_cast<int>(value));
        if (aggregate->priority == priority)
            return false;
        ScopedDataChange data_change(this, PriorityRole);
        aggregate->priority = priority;
        return true;
    }
    case ColorRole: {
        Aggregate *aggregate = this->aggregate();
        const int color = qBound(0x000000, intFromColor(value), 0xffffff);
        if (aggregate->color == color)
            return false;
        ScopedDataChange data_change(this, ColorRole);
        aggregate->color = color;
        return true;
    }
    case VisibilityRole: {
        Aggregate *aggregate = this->aggregate();
        const bool visible = qvariant_cast<bool>(value);
        if (aggregate->visible == visible)
            return false;
        ScopedDataChange data_change(this, VisibilityRole);
        aggregate->visible = visible;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
