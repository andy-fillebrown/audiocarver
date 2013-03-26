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

#include "mi_core_object_modelitem.h"
#include "mi_core_object_aggregate.h"
#include "mi_core_namespace.h"
#include "mi_core_scopedparentchange.h"
#include <iaggregate.h>

using namespace Mi;
using namespace Qt;

namespace Object {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

int ModelItem::itemType() const
{
    return UnknownItem;
}

void ModelItem::setParent(IModelItem *parent)
{
    aggregate()->setParent(parent ? query<IAggregate>(parent) : 0);
}

int ModelItem::roleCount() const
{
    return Aggregate::RoleCount;
}

int ModelItem::roleAt(int i) const
{
    Q_ASSERT(0 <= i);
    Q_ASSERT(i < Aggregate::RoleCount);
    if (i < 0 || Aggregate::RoleCount <= i)
        return -1;
    return NameRole;
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case DisplayRole:
    case NameRole:
        return aggregate()->name();
    case ItemTypeRole:
        return itemType();
    default:
        return QVariant();
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case EditRole:
    case NameRole:
        return aggregate()->setName(qvariant_cast<QString>(value));
    default:
        Q_ASSERT(false);
        return false;
    }
}

}
