/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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
#include <igraphicsgriplist.h>

using namespace Ac;

namespace Track {

void GraphicsItem::update(int role, const QVariant &value)
{
    if (HighlightRole == role)
        return;
    if (VolumeRole == role)
        return;
    IGraphicsItem *note_list = findItem(NoteListItem);
    const int note_count = note_list->itemCount();
    if (VisibilityRole == role && !qvariant_cast<bool>(value)) {
        for (int i = 0;  i < note_count;  ++i)
            note_list->itemAt(i)->update(HighlightRole, NoHighlight);
    }
    for (int i = 0;  i < note_count;  ++i)
        note_list->itemAt(i)->update(role, value);
    ScoreObject::GraphicsItem::update(role, value);
}

}
