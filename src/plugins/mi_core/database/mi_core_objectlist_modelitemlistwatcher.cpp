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

#include "mi_core_objectlist_modelitemlistwatcher.h"
#include <iaggregate.h>
#include <imodel.h>

namespace ObjectList {

IUnknown *ModelItemListWatcher::initialize()
{
    return aggregate()->append(this);
}

void *ModelItemListWatcher::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelItemListWatcher*>(this);
    return aggregate()->queryInterface(interfaceType);
}

void ModelItemListWatcher::beginInsertItem(const IModelItemList *list, int index)
{
    IModel::instance()->beginInsertItem(list, index);
}

void ModelItemListWatcher::endInsertItem(const IModelItemList *list, int index)
{
    IModel::instance()->endInsertItem(list, index);
}

void ModelItemListWatcher::beginRemoveItem(const IModelItemList *list, int index)
{
    IModel::instance()->beginRemoveItem(list, index);
}

void ModelItemListWatcher::endRemoveItem(const IModelItemList *list, int index)
{
    IModel::instance()->endRemoveItem(list, index);
}

}
