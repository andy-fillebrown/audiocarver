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

#include "mi_core_dataobject.h"

#include <mi_idatabase.h>
#include <mi_iorphanage.h>

#include <mi_core_dataobjectlist.h>
#include <mi_core_scopeddatachange.h>
#include <mi_core_scopedparentchange.h>

namespace Mi {
namespace Core {

IAggregator *DataObject::init()
{
    return this;
}

IAggregate *DataObject::ModelData::init()
{
    _item = query<IModelItem>(a());
    return this;
}

IAggregate *DataObject::ModelItem::init()
{
    return this;
}

bool DataObject::setName(const QString &name)
{
    if (_name == name)
        return false;
    if (!name.isEmpty() && _parent && _parent->isList()) {
        IModelList *list = query<IModelList>(_parent);
        if (list && list->containsObjectNamed(_name))
            return false;
    }
    ScopedDataChange data_change(this, NameRole);
    _name = name;
    return true;
}

void DataObject::setParent(DataObject *parent)
{
    if (_parent == parent)
        return;
    ScopedParentChange parent_change(this);
    IOrphanage *orphanage = query<IOrphanage>(IDatabase::instance());
    if (orphanage) {
        if (!_parent)
            orphanage->remove(this);
        if (!parent)
            orphanage->append(this);
    }
    _parent = parent;
}

} // namespace Core
} // namespace Mi
