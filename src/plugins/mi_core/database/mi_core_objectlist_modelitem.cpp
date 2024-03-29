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

#include "mi_core_objectlist_modelitem.h"
#include "mi_core_namespace.h"
#include "mi_core_object_aggregate.h"
#include "mi_core_scopediteminsert.h"
#include "mi_core_scopeditemremove.h"

using namespace Mi;
using namespace Object;
using namespace Qt;

namespace ObjectList {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

void ModelItem::reset()
{
    qDeleteAll(_items);
    _items.clear();
}

int ModelItem::itemType() const
{
    return ListItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ListItem == itemType;
}

IModelItem *ModelItem::parent() const
{
    return query<IModelItem>(aggregate()->parent());
}

bool ModelItem::containsItem(IModelItem *item) const
{
    return _items.contains(query<IAggregate>(item));
}

bool ModelItem::containsItemNamed(const QString &name) const
{
    foreach (IAggregate *item, _items) {
        QString cur_name = get<QString>(query<IModelItem>(item), NameRole);
        if (0 == cur_name.compare(name, CaseInsensitive))
            return true;
    }
    return false;
}

int ModelItem::itemCount() const
{
    return _items.count();
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    return _items.indexOf(query<IAggregate>(item));
}

IModelItem *ModelItem::itemAt(int i) const
{
    return query<IModelItem>(_items.at(i));
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case ListTypeRole:
        return _listType;
    default:
        return Base::ModelItem::getValue(role);
    }
}

void ModelItem::insertItem(int i, IModelItem *item)
{
    IModelItem *old_list = item->parent();
    if (old_list) {
        if (old_list == parent())
            return;
        old_list->removeItem(item);
    }
    const QString name = get<QString>(item, NameRole);
    if (!name.isEmpty()) {
        int suffix = 0;
        QString new_name = name;
        while (containsItemNamed(new_name))
            new_name = QString("%1.%2").arg(name).arg(++suffix);
        if (name != new_name)
            item->set(NameRole, new_name);
    }
    ScopedItemInsert item_insert(this, i);
    _items.insert(i, query<IAggregate>(item));
    item->setParent(this);
}

void ModelItem::removeItemAt(int i)
{
    ScopedItemRemove item_remove(this, i);
    query<IModelItem>(_items.at(i))->setParent(0);
    _items.removeAt(i);
}

}
