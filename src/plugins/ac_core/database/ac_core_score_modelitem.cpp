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

#include "ac_core_score_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <idatabaseobjectfactory.h>
#include <imodelitemlist.h>
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace Score {

ModelItem::ModelItem(IAggregate *aggregate)
    :  ScoreObject::ModelItem(aggregate)
    ,   _tracks(0)
    ,   _gridSettings(0)
    ,   _projectSettings(0)
    ,   _viewSettings(0)
{
    ScoreObject::ModelItem::initialize();
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _tracks = factory->create(TrackListItem, this);
    _gridSettings = factory->create(GridSettingsItem, this);
    _projectSettings = factory->create(ProjectSettingsItem, this);
    _viewSettings = factory->create(ViewSettingsItem, this);
}

ModelItem::~ModelItem()
{
    delete _viewSettings;
    delete _projectSettings;
    delete _gridSettings;
    delete _tracks;
}

int ModelItem::itemType() const
{
    return ScoreItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (ScoreItem == itemType)
        return true;
    return ScoreObject::ModelItem::isTypeOfItem(itemType);
}

int ModelItem::indexOf(const IModelItem *item) const
{
    if (QUERY(IModelItem, _tracks) == item)
        return ItemCountOffset;
    if (QUERY(IModelItem, _gridSettings) == item)
        return ItemCountOffset + 1;
    if (QUERY(IModelItem, _projectSettings) == item)
        return ItemCountOffset + 2;
    if (QUERY(IModelItem, _viewSettings) == item)
        return ItemCountOffset + 3;
    return ScoreObject::ModelItem::indexOf(item);
}

IModelItem *ModelItem::at(int i) const
{
    switch (i - ItemCountOffset) {
    case 0:
        return QUERY(IModelItem, _tracks);
    case 1:
        return QUERY(IModelItem, _gridSettings);
    case 2:
        return QUERY(IModelItem, _projectSettings);
    case 3:
        return QUERY(IModelItem, _viewSettings);
    default:
        return ScoreObject::ModelItem::at(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case GridSettingsItem:
        return QUERY(IModelItem, _gridSettings);
    case ProjectSettingsItem:
        return QUERY(IModelItem, _projectSettings);
    case ViewSettingsItem:
        return QUERY(IModelItem, _viewSettings);
    default:
        return ScoreObject::ModelItem::findItem(itemType);
    }
}

IModelItemList *ModelItem::findList(int listType) const
{
    switch (listType) {
    case TrackItem:
        return QUERY(IModelItemList, _tracks);
    default:
        return ScoreObject::ModelItem::findList(listType);
    }
}

void ModelItem::reset()
{
    IModelData *data = QUERY(IModelData, this);
    data->set(DEFAULT_SCORE_LENGTH, LengthRole);
    data->set(DEFAULT_SCORE_STARTTIME, StartTimeRole);
    ScoreObject::ModelItem::reset();
}

}
