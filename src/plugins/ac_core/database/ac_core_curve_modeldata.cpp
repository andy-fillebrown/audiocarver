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

#include "ac_core_curve_modeldata.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace Curve {

ModelData::ModelData(IAggregate *aggregate)
    :   Object::ModelData(aggregate)
{}

bool ModelData::setPoints(const PointList &points)
{
    const PointList old_points = _points;
    _points = points;
    conformPoints();
    if (_points == old_points)
        return false;
    const PointList new_points = _points;
    _points = old_points;
    ScopedDataChange data_change(this, PointsRole);
    _points = new_points;
    return true;
}

int ModelData::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return PointsRole;
    default:
        return Object::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case PointsRole:
        return QVariant::fromValue(_points);
    default:
        return Object::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case PointsRole:
        return setPoints(qvariant_cast<PointList>(value));
    default:
        return Object::ModelData::setValue(value, role);
    }
}

}
