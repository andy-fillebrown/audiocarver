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

#include "scoreobject_modelitem.h"
#include "ac_core_namespace.h"
#include <interfaces/iaggregate.h>
#include <interfaces/idatabaseobjectfactory.h>
#include <interfaces/imodelitemlist.h>

using namespace Ac;

namespace ScoreObject {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Base::ModelItem(aggregate)
    ,   _pitchCurve(0)
    ,   _controlCurves(0)
{}

ModelItem::~ModelItem()
{
    delete _controlCurves;
    delete _pitchCurve;
}

IUnknown *ModelItem::initialize()
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _pitchCurve = factory->create(PitchCurveItem, this);
    _controlCurves = factory->create(ControlCurveListItem, this);
    return Base::ModelItem::initialize();
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ScoreObjectItem == itemType;
}

int ModelItem::count() const
{
    return TotalItemCount;
}

int ModelItem::indexOf(IModelItem *item) const
{
    if (query<IModelItem>(pitchCurve()) == item)
        return ItemCountOffset;
    if (query<IModelItem>(controlCurves()) == item)
        return ItemCountOffset + 1;
    return Base::ModelItem::indexOf(item);
}

IModelItem *ModelItem::at(int i) const
{
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(pitchCurve());
    case 1:
        return query<IModelItem>(controlCurves());
    default:
        return Base::ModelItem::at(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case PitchCurveItem:
        return query<IModelItem>(pitchCurve());
    default:
        return Base::ModelItem::findItem(itemType);
    }
}

IModelItemList *ModelItem::findList(int listType) const
{
    switch (listType) {
    case ControlCurveItem:
        return query<IModelItemList>(controlCurves());
    default:
        return Base::ModelItem::findList(listType);
    }
}

}
