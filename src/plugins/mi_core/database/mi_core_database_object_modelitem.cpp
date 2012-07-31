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

#include "mi_core_database_object_modelitem.h"

#include "mi_iaggregate.h"
#include "mi_imodelitemlist.h"

#include "mi_core_database_objectlist_aggregate.h"

namespace Mi {
namespace Core {
namespace Database {
namespace Object {

ModelItem::ModelItem(IAggregate *aggregate)
    :   _aggregate(static_cast<Aggregate*>(aggregate))
{
    Q_ASSERT(dynamic_cast<Aggregate*>(aggregate));
}

IUnknown *ModelItem::initialize()
{
    aggregate()->append(this);
    return this;
}

IModelItem *ModelItem::parent() const
{
    return query<IModelItem>(aggregate()->parent());
}

void ModelItem::setParent(IModelItem *parent)
{
    if (!parent) {
        aggregate()->setParent(0);
        return;
    }
    Aggregate *parent_aggregate = dynamic_cast<Aggregate*>(query<IAggregate>(parent));
    aggregate()->setParent(parent_aggregate);
}

IModelItemList *ModelItem::list() const
{
    return query<IModelItemList>(aggregate()->list());
}

}
}
}
}
