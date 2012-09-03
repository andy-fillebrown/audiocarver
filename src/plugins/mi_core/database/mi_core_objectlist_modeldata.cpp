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

#include "mi_core_objectlist_modeldata.h"
#include "mi_core_scopeddatachange.h"
#include <imodelitemlist.h>

using namespace Mi;
using namespace Qt;

namespace ObjectList {

IUnknown *ModelData::initialize()
{
    return aggregate()->append(this);
}

void *ModelData::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelData*>(this);
    return aggregate()->queryInterface(interfaceType);
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case ItemTypeRole:
        return query<IModelItem>(this)->itemType();
    case ListTypeRole:
        return query<IModelItemList>(this)->listType();
    default:
        return QVariant();
    }
}

}