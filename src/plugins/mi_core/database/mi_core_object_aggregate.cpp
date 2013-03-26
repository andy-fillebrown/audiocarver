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

#include "mi_core_object_aggregate.h"
#include "mi_core_scopeddatachange.h"
#include "mi_core_scopedparentchange.h"
#include <imodelitem.h>

using namespace Mi;

namespace Object {

void Aggregate::setParent(IAggregate *parent)
{
    if (this->parent() == parent)
        return;
    ScopedParentChange parent_change(query<IModelItem>(this));
    this->parent() = parent;
}

bool Aggregate::setName(const QString &name)
{
    if (_name == name)
        return false;
    IModelItem *parent = query<IModelItem>(this->parent());
    if (!name.isEmpty() && parent && parent->containsItemNamed(name))
        return false;
    ScopedDataChange data_change(query<IModelItem>(this), NameRole);
    _name = name;
    return true;
}

}
