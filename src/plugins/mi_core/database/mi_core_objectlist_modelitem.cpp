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

#include "mi_core_objectlist_modelitem.h"
#include "mi_core_namespace.h"
#include "mi_core_scopediteminsert.h"
#include "mi_core_scopeditemremove.h"
#include "mi_core_scopedparentchange.h"
#include <iaggregate.h>
#include <imodeldata.h>

using namespace Mi;

namespace ObjectList {

void *ModelItem::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

ModelItem::ModelItem(IAggregate *aggregate, int listType)
    :   _aggregate(aggregate)
    ,   _parent(0)
    ,   _listType(listType)
{
    _aggregate->append(this);
}

int ModelItem::itemType() const
{
    return ListItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ListItem == itemType;
}

void ModelItem::setParent(IModelItem *parent)
{
    if (_parent == parent)
        return;
    ScopedParentChange parent_change(this);
    _parent = parent;
}

bool ModelItem::contains(const QString &name) const
{
    foreach (IModelItem *item, _items)
        if (QUERY(IModelData, item)->get<QString>(NameRole) == name)
            return true;
    return false;
}

void ModelItem::insert(int i, IModelItem *item)
{
    IModelItemList *old_list = item->list();
    if (old_list) {
        if (old_list == list())
            return;
        old_list->remove(item);
    }
    IModelData *data = QUERY(IModelData, item);
    const QString name = data->get<QString>(NameRole);
    if (!name.isEmpty()) {
        int suffix = 0;
        QString new_name = name;
        while (contains(new_name))
            new_name = QString("%1.%2").arg(name).arg(++suffix);
        if (name != new_name)
            data->set(new_name, NameRole);
    }
    ScopedItemInsert item_insert(this, i);
    _items.insert(i, item);
    item->setParent(this);
}

void ModelItem::removeAt(int i)
{
    ScopedItemRemove item_remove(this, i);
    _items.at(i)->setParent(0);
    _items.removeAt(i);
}

void ModelItem::reset()
{
    foreach (IModelItem *item, _items)
        delete QUERY(IAggregate, item);
    _items.clear();
}

}
