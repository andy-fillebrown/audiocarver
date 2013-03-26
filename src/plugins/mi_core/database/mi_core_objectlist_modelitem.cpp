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
#include "mi_core_objectlist_aggregate.h"
#include "mi_core_scopediteminsert.h"
#include "mi_core_scopeditemremove.h"

using namespace Mi;

namespace ObjectList {

ModelItem::ModelItem(IAggregate *aggregate, int listType)
    :   Base::ModelItem(aggregate)
{
    this->aggregate()->listType() = listType;
}

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

int ModelItem::itemType() const
{
    return ListItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ListItem == itemType;
}

bool ModelItem::containsItem(IModelItem *item) const
{
    return aggregate()->items().contains(query<IAggregate>(item));
}

bool ModelItem::containsItemNamed(const QString &name) const
{
    foreach (IAggregate *item, aggregate()->items())
        if (get<QString>(query<IModelItem>(item), NameRole) == name)
            return true;
    return false;
}

int ModelItem::itemCount() const
{
    return aggregate()->items().count();
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    return aggregate()->items().indexOf(query<IAggregate>(item));
}

IModelItem *ModelItem::itemAt(int i) const
{
    return query<IModelItem>(aggregate()->items().at(i));
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case ListTypeRole:
        return aggregate()->listType();
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
    aggregate()->items().insert(i, query<IAggregate>(item));
    item->setParent(this);
}

void ModelItem::removeItemAt(int i)
{
    ScopedItemRemove item_remove(this, i);
    QList<IAggregate*> &items = aggregate()->items();
    query<IModelItem>(items.at(i))->setParent(0);
    items.removeAt(i);
}

}
