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
#include "mi_core_scopeddatachange.h"
#include "mi_core_scopedparentchange.h"
#include <mi_core_namespace.h>
#include <QtDebug>

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

IModelItem *ModelItem::parent() const
{
    return query<IModelItem>(aggregate()->parent);
}

void ModelItem::setParent(IModelItem *parent)
{
    if (this->parent() == parent)
        return;
    ScopedParentChange parent_change(this);
    aggregate()->parent = query<IAggregate>(parent);
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
        return aggregate()->name;
    default:
        return Base::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case EditRole:
    case NameRole: {
        QString name = qvariant_cast<QString>(value);
        if (aggregate()->name == name)
            return false;
        IModelItem *parent = this->parent();
        if (!name.isEmpty() && parent && parent->containsItemNamed(name))
            return false;
        ScopedDataChange data_change(this, NameRole);
        aggregate()->name = name;
        return true;
    }
    default:
        qWarning() << Q_FUNC_INFO << QString("invalid role (%1)").arg(itemDataRoleString(role));
        return false;
    }
}

}
