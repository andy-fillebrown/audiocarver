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

#include "mi_core_objectlist_modelitemlistupdater.h"
#include <iaggregate.h>
#include <imodel.h>

namespace ObjectList {

ModelItemListUpdater::ModelItemListUpdater(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    _aggregate->append(this);
}

void *ModelItemListUpdater::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

void ModelItemListUpdater::beginInsertItem(const IModelItemList *list, int index)
{
    IModel::instance()->beginInsertItem(list, index);
}

void ModelItemListUpdater::endInsertItem(const IModelItemList *list, int index)
{
    IModel::instance()->endInsertItem(list, index);
}

void ModelItemListUpdater::beginRemoveItem(const IModelItemList *list, int index)
{
    IModel::instance()->beginRemoveItem(list, index);
}

void ModelItemListUpdater::endRemoveItem(const IModelItemList *list, int index)
{
    IModel::instance()->endRemoveItem(list, index);
}

}
