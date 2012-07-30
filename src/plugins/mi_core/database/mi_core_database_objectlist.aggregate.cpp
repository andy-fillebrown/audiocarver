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

#include "mi_core_database_objectlist.aggregate.h"

#include "mi_imodeldata.h"
#include "mi_imodelitemlist.h"

namespace Mi {
namespace Core {
namespace Database {
namespace ObjectList {

IAggregate *Aggregate::initialize()
{
    setName(itemTypeString(_listType) + "s");
    return Object::Aggregate::initialize();
}

Aggregate::~Aggregate()
{
    clear();
}

bool Aggregate::contains(const QString &name) const
{
    foreach (IAggregate *object, objects())
        if (query<IModelData>(object)->get<QString>(NameRole) == name)
            return true;
    return false;
}

void Aggregate::insert(int i, IAggregate *object)
{
    IModelItem *item = query<IModelItem>(object);
    IModelItemList *old_list = query<IModelItemList>(item->parent());
    if (old_list) {
        if (old_list == query<IModelItemList>(this))
            return;
        old_list->remove(item);
    }
    IModelData *data = query<IModelData>(object);
    const QString name = data->get<QString>(NameRole);
    if (!name.isEmpty()) {
        int suffix = 0;
        QString new_name = name;
        while (contains(new_name))
            new_name = QString("%1.%2").arg(name).arg(++suffix);
        if (name != new_name)
            data->set(new_name, NameRole);
    }
    _objects.insert(i, object);
    dynamic_cast<Object::Aggregate*>(query<IAggregate>(item))->setParent(this);
}

}
}
}
}
