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

#include "ac_gui_track_entity.h"
#include <ac_core_namespace.h>
#include <imodelitemlist.h>

using namespace Ac;

namespace Track {

IUnknown *Entity::initialize()
{
    return ScoreObject::Entity::initialize();
}

void Entity::update(int role)
{
    switch (role) {
    case ColorRole: {
        IModelItem *track_item = query<IModelItem>(this);
        if (!track_item)
            return;
        IModelItemList *note_list = track_item->findList(NoteItem);
        const int note_count = note_list->count();
        for (int i = 0;  i < note_count;  ++i) {
            IEntity *note_entity = query<IEntity>(note_list->at(i));
            if (!note_entity)
                continue;
            note_entity->update(ColorRole);
        }
    } break;
    }
}

}
