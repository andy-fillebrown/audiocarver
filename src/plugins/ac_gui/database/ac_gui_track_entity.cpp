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

#include "ac_gui_track_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>
#include <imodeldata.h>
#include <imodelitemlist.h>
#include <QGraphicsItem>

using namespace Ac;

namespace Track {

IUnknown *GraphicsItem::initialize()
{
    return ScoreObject::GraphicsItem::initialize();
}

void GraphicsItem::update(int role)
{
    switch (role) {
    case ColorRole: {
        IModelItem *track_item = query<IModelItem>(this);
        if (!track_item)
            return;
        IModelItemList *note_list = track_item->findList(NoteItem);
        const int note_count = note_list->count();
        for (int i = 0;  i < note_count;  ++i) {
            IGraphicsItem *note_item = query<IGraphicsItem>(note_list->at(i));
            if (!note_item)
                continue;
            note_item->update(ColorRole);
        }
    } break;
    case VisibilityRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const bool visible = data->get<bool>(VisibilityRole);
        node(PitchScene, MainTransform)->setVisible(visible);
        node(ControlScene, MainTransform)->setVisible(visible);
    }   break;
    }
}

}
