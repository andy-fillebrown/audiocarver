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

#include "ac_core_track_modelitem.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>
#include <idatabaseobjectfactory.h>
#include <imodelitemlist.h>

using namespace Ac;

namespace Track {

IUnknown *ModelItem::initialize()
{
    _notes = IDatabaseObjectFactory::instance()->create(NoteListItem, this);
    return ScoreObject::ModelItem::initialize();
}

ModelItem::~ModelItem()
{
    delete _notes;
}

int ModelItem::itemType() const
{
    return TrackItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (TrackItem == itemType)
        return true;
    return ScoreObject::ModelItem::isTypeOfItem(itemType);
}

int ModelItem::indexOf(const IModelItem *item) const
{
    if (query<IModelItem>(notes()) == item)
        return ItemCountOffset;
    return ScoreObject::ModelItem::indexOf(item);
}

IModelItem *ModelItem::at(int i) const
{
    Q_ASSERT(0 <= (TotalItemCount - i));
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(notes());
    default:
        return ScoreObject::ModelItem::at(i);
    }
}

IModelItemList *ModelItem::findList(int listType) const
{
    switch (listType) {
    case NoteItem:
        return query<IModelItemList>(notes());
    default:
        return ScoreObject::ModelItem::findList(listType);
    }
}

}