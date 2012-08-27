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

#include "mi_core_objectlist_modelitemwatcher.h"
#include <iaggregate.h>
#include <imodel.h>

namespace ObjectList {

IUnknown *ModelItemWatcher::initialize()
{
    return aggregate()->append(this);
}

void *ModelItemWatcher::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelItemWatcher*>(this);
    return aggregate()->queryInterface(interfaceType);
}

void ModelItemWatcher::beginInsertItem(const IModelItem *parent, int index)
{
    IModel::instance()->beginInsertItem(parent, index);
}

void ModelItemWatcher::endInsertItem(const IModelItem *parent, int index)
{
    IModel::instance()->endInsertItem(parent, index);
}

void ModelItemWatcher::beginRemoveItem(const IModelItem *parent, int index)
{
    IModel::instance()->beginRemoveItem(parent, index);
}

void ModelItemWatcher::endRemoveItem(const IModelItem *parent, int index)
{
    IModel::instance()->endRemoveItem(parent, index);
}

}
