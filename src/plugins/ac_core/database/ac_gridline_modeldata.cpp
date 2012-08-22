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

#include "ac_gridline_modeldata.h"
#include "ac_core_namespace.h"
#include <mi_scopeddatachange.h>
#include <mi_utilities.h>

using namespace Ac;

namespace GridLine {

ModelData::ModelData(IAggregate *aggregate)
    :   Base::ModelData(aggregate)
    ,   _location(0.0f)
    ,   _priority(0)
    ,   _color(lightGray)
{}

IUnknown *ModelData::initialize()
{
    return Base::ModelData::initialize();
}

bool ModelData::setLocation(qreal location)
{
    location = qMax(qreal(0.0f), location);
    if (_location == location)
        return false;
    ScopedDataChange data_change(this, LocationRole);
    _location = location;
    return true;
}

bool ModelData::setLabel(const QString &label)
{
    if (_label == label)
        return false;
    ScopedDataChange data_change(this, LabelRole);
    _label = label;
    return true;
}

bool ModelData::setPriority(int priority)
{
    priority = qMax(0, priority);
    if (_priority == priority)
        return false;
    ScopedDataChange data_change(this, PriorityRole);
    _priority = priority;
    return true;
}

bool ModelData::setColor(int color)
{
    color = qBound(0x000000, color, 0xffffff);
    if (_color == color)
        return false;
    ScopedDataChange data_change(this, ColorRole);
    _color = color;
    return true;
}

int ModelData::roleAt(int i) const
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
        return Base::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case LocationRole:
        return location();
    case LabelRole:
        return label();
    case PriorityRole:
        return priority();
    case ColorRole:
        return intToColorString(color());
    default:
        return Base::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case LocationRole:
        return setLocation(qvariant_cast<qreal>(value));
    case LabelRole:
        return setLabel(qvariant_cast<QString>(value));
    case PriorityRole:
        return setPriority(qvariant_cast<int>(value));
    case ColorRole:
        return setColor(colorStringToInt(qvariant_cast<QString>(value)));
    default:
        return Base::ModelData::setValue(value, role);
    }
}

}
