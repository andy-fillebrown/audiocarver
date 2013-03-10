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

#include "mi_core_object_modeldata.h"
#include "mi_core_scopeddatachange.h"
#include <iaggregate.h>
#include <imodeliteminfo.h>
#include <imodelitemlist.h>

using namespace Mi;
using namespace Qt;

namespace Object {

bool ModelData::setName(const QString &name)
{
    if (_name == name)
        return false;
    IModelItem *parent = QUERY(IModelItem, this)->parent();
    if (!name.isEmpty() && parent && parent->isList()) {
        IModelItemList *list = QUERY(IModelItemList, parent);
        if (list && list->contains(name))
            return false;
    }
    ScopedDataChange data_change(this, NameRole);
    _name = name;
    return true;
}

int ModelData::roleAt(int i) const
{
    Q_ASSERT(0 <= i);
    Q_ASSERT(i < RoleCount);
    if (i < 0 || RoleCount <= i)
        return -1;
    return NameRole;
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case DisplayRole:
    case NameRole:
        return name();
    case ItemTypeRole:
        return QUERY(IModelItemInfo, this)->itemType();
    default:
        return QVariant();
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case EditRole:
    case NameRole:
        return setName(qvariant_cast<QString>(value));
    default:
        Q_ASSERT(0);
        return false;
    }
}

}
