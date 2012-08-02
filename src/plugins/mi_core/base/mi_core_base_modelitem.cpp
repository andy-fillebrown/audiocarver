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

#include "mi_core_scopedparentchange.h"

namespace Base {

IUnknown *ModelItem::initialize()
{
    aggregate()->append(this);
    return this;
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
