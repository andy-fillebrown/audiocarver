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

IUnknown *ModelItem::initialize()
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _tracks = factory->create(TrackListItem, this);
    _gridSettings = factory->create(GridSettingsItem, this);
    _projectSettings = factory->create(ProjectSettingsItem, this);
    _viewSettings = factory->create(ViewSettingsItem, this);
    return ScoreObject::ModelItem::initialize();
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

int ModelItem::indexOf(IModelItem *item) const
{
    if (query<IModelItem>(tracks()) == item)
        return ItemCountOffset;
    if (query<IModelItem>(gridSettings()) == item)
        return ItemCountOffset + 1;
    if (query<IModelItem>(projectSettings()) == item)
        return ItemCountOffset + 2;
    if (query<IModelItem>(viewSettings()) == item)
        return ItemCountOffset + 3;
    return ScoreObject::ModelItem::indexOf(item);
}

IModelItem *ModelItem::at(int i) const
{
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(tracks());
    case 1:
        return query<IModelItem>(gridSettings());
    case 2:
        return query<IModelItem>(projectSettings());
    case 3:
        return query<IModelItem>(viewSettings());
    default:
        return ScoreObject::ModelItem::at(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case GridSettingsItem:
        return query<IModelItem>(gridSettings());
    case ProjectSettingsItem:
        return query<IModelItem>(projectSettings());
    case ViewSettingsItem:
        return query<IModelItem>(viewSettings());
    default:
        return ScoreObject::ModelItem::findItem(itemType);
    }
}

IModelItemList *ModelItem::findList(int listType) const
{
    switch (listType) {
    case TrackItem:
        return query<IModelItemList>(tracks());
    default:
        return ScoreObject::ModelItem::findList(listType);
    }
}

void ModelItem::reset()
{
    IModelData *data = query<IModelData>(this);
    data->set(DEFAULT_SCORE_LENGTH, LengthRole);
    data->set(DEFAULT_SCORE_STARTTIME, StartTimeRole);
    ScoreObject::ModelItem::reset();
}

}
