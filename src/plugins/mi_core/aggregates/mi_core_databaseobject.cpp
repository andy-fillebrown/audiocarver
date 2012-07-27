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

#include "mi_core_databaseobject.h"

#include <mi_idatabase.h>
#include <mi_imodelitemlist.h>

#include <mi_core_databaseobjectlist.h>
#include <mi_core_scopeddatachange.h>
#include <mi_core_scopedparentchange.h>

namespace Mi {
namespace Core {

IAggregate *DatabaseObject::initialize()
{
    return this;
}

bool DatabaseObject::setName(const QString &name)
{
    if (_name == name)
        return false;
    if (!name.isEmpty() && _parent && _parent->isList()) {
        IModelItemList *list = query<IModelItemList>(_parent);
        if (list && list->contains(name))
            return false;
    }
    ScopedDataChange data_change(this, NameRole);
    _name = name;
    return true;
}

void DatabaseObject::setParent(DatabaseObject *parent)
{
    if (_parent == parent)
        return;
    ScopedParentChange parent_change(this);
    _parent = parent;
}

DatabaseObjectList *DatabaseObject::list() const
{
    if (_parent && _parent->isList())
        return dynamic_cast<DatabaseObjectList*>(_parent);
    return 0;
}

IUnknown *DatabaseObject::ModelData::initialize()
{
    _item = query<IModelItem>(aggregate());
    return this;
}

IUnknown *DatabaseObject::ModelItem::initialize()
{
    return this;
}

IModelItemList *DatabaseObject::ModelItem::list() const
{
    return query<IModelItemList>(aggregate()->list());
}

} // namespace Core
} // namespace Mi
