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

#include "ac_core_database_scoreobject_modelitem.h"

#include <mi_imodelitemlist.h>

#include "ac_core_database_scoreobject_aggregate.h"
#include "ac_core_namespace.h"

#include <mi_core_scopeddatachange.h>

namespace Ac {
namespace Core {
namespace Database {
namespace ScoreObject {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(ModelItem_BaseClass::aggregate());
}

ModelItem::ModelItem(IAggregate *aggregate)
    :   ModelItem_BaseClass(aggregate)
{
    Q_ASSERT(dynamic_cast<Aggregate*>(aggregate));
}

IUnknown *ModelItem::initialize()
{
    return ModelItem_BaseClass::initialize();
}

int ModelItem::count() const
{
    return Aggregate::TotalItemCount;
}

int ModelItem::indexOf(const IModelItem *item) const
{
    const Aggregate *aggregate = this->aggregate();
    if (query<IModelItem>(aggregate->pitchCurve()) == item)
        return Aggregate::ItemCountOffset;
    if (query<IModelItem>(aggregate->controlCurves()) == item)
        return Aggregate::ItemCountOffset + 1;
    return ModelItem_BaseClass::indexOf(item);
}

IModelItem *ModelItem::at(int i) const
{
    switch (i - Aggregate::ItemCountOffset) {
    case 0:
        return query<IModelItem>(aggregate()->pitchCurve());
    case 1:
        return query<IModelItem>(aggregate()->controlCurves());
    default:
        return ModelItem_BaseClass::at(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case PitchCurveItem:
        return query<IModelItem>(aggregate()->pitchCurve());
    default:
        return ModelItem_BaseClass::findItem(itemType);
    }
}

IModelItemList *ModelItem::findList(int listType) const
{
    switch (listType) {
    case ControlCurveItem:
        return query<IModelItemList>(aggregate()->controlCurves());
    default:
        return ModelItem_BaseClass::findList(listType);
    }
}

}
}
}
}
