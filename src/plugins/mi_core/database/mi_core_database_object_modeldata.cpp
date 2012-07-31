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

#include "mi_core_database_object_modeldata.h"

#include "mi_core_database_object_aggregate.h"

namespace Mi {
namespace Core {
namespace Database {
namespace Object {

ModelData::ModelData(IAggregate *aggregate)
    :   _aggregate(static_cast<Aggregate*>(aggregate))
{
    Q_ASSERT(dynamic_cast<Aggregate*>(_aggregate));
}

IUnknown *ModelData::initialize()
{
    aggregate()->append(this);
    return this;
}

int ModelData::roleCount() const
{
    return Aggregate::TotalRoleCount;
}

int ModelData::roleAt(int i) const
{
    Q_ASSERT(0 <= i);
    Q_ASSERT(i < Aggregate::RoleCount);
    if (i < 0 || Aggregate::RoleCount <= i)
        return -1;
    return NameRole;
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return aggregate()->name();
    default:
        Q_ASSERT(0);
        return QVariant();
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case Qt::EditRole:
    case NameRole:
        return aggregate()->setName(qvariant_cast<QString>(value));
    default:
        Q_ASSERT(0);
        return false;
    }
}

}
}
}
}
