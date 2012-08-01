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

#include "mi_core_database_objectlist_modelitemlist.h"

#include "mi_iaggregate.h"
#include "mi_imodeldata.h"

#include "mi_core_database_objectlist_aggregate.h"
#include "mi_core_scopedparentchange.h"

namespace Mi {
namespace Core {
namespace Database {
namespace ObjectList {

IUnknown *ModelItemList::initialize()
{
    aggregate()->append(this);
    return this;
}

void ModelItemList::setParent(IModelItem *parent)
{
    if (_parent == parent)
        return;
    ScopedParentChange parent_change(this);
    _parent = parent;
}

bool ModelItemList::contains(const QString &name) const
{
    foreach (IModelItem *item, _items)
        if (query<IModelData>(item)->get<QString>(NameRole) == name)
            return true;
    return false;
}

void ModelItemList::insert(int i, IModelItem *item)
{
    IModelItemList *old_list = item->list();
    if (old_list) {
        if (old_list == list())
            return;
        old_list->remove(item);
    }
    IModelData *data = query<IModelData>(item);
    const QString name = data->get<QString>(NameRole);
    if (!name.isEmpty()) {
        int suffix = 0;
        QString new_name = name;
        while (contains(new_name))
            new_name = QString("%1.%2").arg(name).arg(++suffix);
        if (name != new_name)
            data->set(new_name, NameRole);
    }
    _items.insert(i, item);
    item->setParent(this);
}

void ModelItemList::removeAt(int i)
{
    _items.removeAt(i);
}

void ModelItemList::clear()
{
    foreach (IModelItem *item, _items)
        delete query<IAggregate>(item);
    _items.clear();
}

}
}
}
}
