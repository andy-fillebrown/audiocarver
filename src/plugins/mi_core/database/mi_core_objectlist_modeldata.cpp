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

#include "mi_core_objectlist_modeldata.h"
#include "mi_core_namespace.h"
#include <imodelitemlist.h>

using namespace Mi;

namespace ObjectList {

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case ListTypeRole:
        return QUERY(IModelItemList, this)->listType();
    default:
        return Object::ModelData::getValue(role);
    }
}

}