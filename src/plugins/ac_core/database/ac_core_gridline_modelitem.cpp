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
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>
#include <mi_core_utilities.h>

using namespace Ac;
using namespace Mi;

namespace GridLine {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Object::ModelItem(aggregate)
    ,   _location(Q_FLOAT_MIN)
    ,   _priority(0)
    ,   _color(DEFAULT_GRIDLINE_COLOR)
    ,   _visible(true)
{}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return GridLineItem == itemType;
}

int ModelItem::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
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
        return _location;
    case LabelRole:
        return _label;
    case PriorityRole:
        return _priority;
    case ColorRole:
        return colorFromInt(_color);
    case VisibilityRole:
        return _visible;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case LocationRole: {
        const qreal location = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (_location == location)
            return false;
        ScopedDataChange data_change(this, LocationRole);
        _location = location;
        return true;
    }
    case LabelRole: {
        const QString label = qvariant_cast<QString>(value);
        if (_label == label)
            return false;
        ScopedDataChange data_change(this, LabelRole);
        _label = label;
        return true;
    }
    case PriorityRole: {
        const int priority = qMax(0, qvariant_cast<int>(value));
        if (_priority == priority)
            return false;
        ScopedDataChange data_change(this, PriorityRole);
        _priority = priority;
        return true;
    }
    case ColorRole: {
        const int color = qBound(0x000000, intFromColor(value), 0xffffff);
        if (_color == color)
            return false;
        ScopedDataChange data_change(this, ColorRole);
        _color = color;
        return true;
    }
    case VisibilityRole: {
        const bool visible = qvariant_cast<bool>(value);
        if (_visible == visible)
            return false;
        ScopedDataChange data_change(this, VisibilityRole);
        _visible = visible;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
