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

#include "ac_core_gridsettings_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>
#include <imodeldata.h>
#include <imodelitemlist.h>

using namespace Ac;

namespace GridSettings {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Object::ModelItem(aggregate)
    ,   _timeGridLines(0)
    ,   _pitchGridLines(0)
    ,   _controlGridLines(0)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _timeGridLines = factory->create(TimeGridLineListItem, this);
    _pitchGridLines = factory->create(PitchGridLineListItem, this);
    _controlGridLines = factory->create(ControlGridLineListItem, this);
}

ModelItem::~ModelItem()
{
    delete _controlGridLines;
    delete _pitchGridLines;
    delete _timeGridLines;
}

int ModelItem::itemType() const
{
    return GridSettingsItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (GridSettingsItem == itemType)
        return true;
    return Object::ModelItem::isTypeOfItem(itemType);
}

int ModelItem::indexOf(const IModelItem *item) const
{
    if (query<IModelItem>(_timeGridLines) == item)
        return ItemCountOffset;
    if (query<IModelItem>(_pitchGridLines) == item)
        return ItemCountOffset + 1;
    if (query<IModelItem>(_controlGridLines) == item)
        return ItemCountOffset + 2;
    return Object::ModelItem::indexOf(item);
}

IModelItem *ModelItem::at(int i) const
{
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(_timeGridLines);
    case 1:
        return query<IModelItem>(_pitchGridLines);
    case 2:
        return query<IModelItem>(_controlGridLines);
    default:
        return Object::ModelItem::at(i);
    }
}

IModelItemList *ModelItem::findList(int listType) const
{
    switch (listType) {
    case TimeGridLineItem:
        return query<IModelItemList>(_timeGridLines);
    case PitchGridLineItem:
        return query<IModelItemList>(_pitchGridLines);
    case ControlGridLineItem:
        return query<IModelItemList>(_controlGridLines);
    default:
        return Object::ModelItem::findList(listType);
    }
}

void ModelItem::reset()
{
    IModelData *data = query<IModelData>(this);
    data->set(DEFAULT_GRIDSETTINGS_SNAPENABLED, SnapEnabledRole);
    data->set(DEFAULT_GRIDSETTINGS_GRIDSNAPENABLED, GridSnapEnabledRole);
    data->set(DEFAULT_GRIDSETTINGS_TIMESNAP, TimeSnapRole);
    data->set(DEFAULT_GRIDSETTINGS_PITCHSNAP, PitchSnapRole);
    data->set(DEFAULT_GRIDSETTINGS_CONTROLSNAP, ControlSnapRole);
    Object::ModelItem::reset();
}

}
