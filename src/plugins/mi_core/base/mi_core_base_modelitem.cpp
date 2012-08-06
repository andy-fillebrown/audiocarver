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

#include "mi_core_base_modelitem.h"
#include "mi_core_imodelitemlist.h"
#include "mi_core_namespace.h"
#include "mi_core_scopedparentchange.h"

using namespace Mi;

namespace Base {

void *ModelItem::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelItem*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *ModelItem::initialize()
{
    return aggregate()->append(this);
}

int ModelItem::itemType() const
{
    return UnknownItem;
}

void ModelItem::setParent(IModelItem *parent)
{
    if (_parent == parent)
        return;
    ScopedParentChange parent_change(this);
    _parent = parent;
}

IModelItemList *ModelItem::list() const
{
    return query<IModelItemList>(parent());
}

}
