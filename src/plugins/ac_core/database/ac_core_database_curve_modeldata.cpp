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

#include "ac_core_database_curve_modeldata.h"

#include "ac_core_database_curve_aggregate.h"
#include "ac_core_point.h"

#include <mi_core_scopeddatachange.h>

namespace Ac {
namespace Core {
namespace Database {
namespace Curve {

Aggregate *ModelData::aggregate() const
{
    return static_cast<Aggregate*>(ModelData_BaseClass::aggregate());
}

ModelData::ModelData(IAggregate *aggregate)
    :   ModelData_BaseClass(aggregate)
{
    Q_ASSERT(dynamic_cast<Aggregate*>(aggregate));
}

IUnknown *ModelData::initialize()
{
    return ModelData_BaseClass::initialize();
}

int ModelData::roleCount() const
{
    return Aggregate::TotalRoleCount;
}

int ModelData::roleAt(int i) const
{
    switch (i - Aggregate::RoleCountOffset) {
    case 0:
        return PointsRole;
    default:
        return ModelData_BaseClass::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case PointsRole:
        return QVariant::fromValue(aggregate()->points());
    default:
        return ModelData_BaseClass::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case PointsRole:
        return aggregate()->setPoints(qvariant_cast<PointList>(value));
    default:
        return ModelData_BaseClass::setValue(value, role);
    }
}

}
}
}
}
