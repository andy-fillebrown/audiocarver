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

#include "mi_core_database_objectlist_modelitemlist.h"

#include "mi_iaggregate.h"

#include "mi_core_database_objectlist_aggregate.h"

namespace Mi {
namespace Core {
namespace Database {
namespace ObjectList {

ModelItemList::ModelItemList(IAggregate *aggregate)
    :   _aggregate(static_cast<Aggregate*>(aggregate))
{
    Q_ASSERT(dynamic_cast<Aggregate*>(aggregate));
}

IUnknown *ModelItemList::initialize()
{
    aggregate()->append(this);
    return this;
}

IModelItem *ModelItemList::parent() const
{
    return query<IModelItem>(aggregate()->parent());
}

void ModelItemList::setParent(IModelItem *parent)
{
    if (!parent) {
        aggregate()->setParent(0);
        return;
    }
    Object::Aggregate *parent_aggregate = dynamic_cast<Object::Aggregate*>(query<IAggregate>(parent));
    aggregate()->setParent(parent_aggregate);
}

int ModelItemList::count() const
{
    return aggregate()->objects().count();
}

int ModelItemList::indexOf(const IModelItem *item) const
{
    return aggregate()->objects().indexOf(query<IAggregate>(item));
}

IModelItem *ModelItemList::at(int i) const
{
    return query<IModelItem>(aggregate()->objects().at(i));
}

int ModelItemList::listType() const
{
    return aggregate()->listType();
}

bool ModelItemList::contains(const QString &name) const
{
    return aggregate()->contains(name);
}

void ModelItemList::insert(int i, IModelItem *item)
{
    aggregate()->insert(i, dynamic_cast<Object::Aggregate*>(query<IAggregate>(item)));
}

void ModelItemList::removeAt(int i)
{
    QList<IAggregate*> &objects = aggregate()->objects();
    dynamic_cast<Object::Aggregate*>(objects.at(i))->setParent(0);
    objects.removeAt(i);
}

void ModelItemList::clear()
{
    aggregate()->clear();
}

}
}
}
}
