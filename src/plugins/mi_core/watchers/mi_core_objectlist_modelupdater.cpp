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

#include "mi_core_objectlist_modelupdater.h"
#include <imodel.h>

namespace ObjectList {

void ModelUpdater::beginInsertItem(IModelItem *list, int index)
{
    IModel::instance()->beginInsertItem(list, index);
}

void ModelUpdater::endInsertItem(IModelItem *list, int index)
{
    IModel::instance()->endInsertItem(list, index);
}

void ModelUpdater::beginRemoveItem(IModelItem *list, int index)
{
    IModel::instance()->beginRemoveItem(list, index);
}

void ModelUpdater::endRemoveItem(IModelItem *list, int index)
{
    IModel::instance()->endRemoveItem(list, index);
}

}
