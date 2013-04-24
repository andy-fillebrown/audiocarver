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

#include "ac_gui_object_selectionupdater.h"
#include "ac_gui_graphicsviewmanager.h"
#include <ac_core_namespace.h>
#include <ieditor.h>
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <iselectionset.h>

using namespace Ac;

namespace Object {

void SelectionUpdater::endChangeSelection(const ISelectionSet *selectionSet)
{
    const QList<IGraphicsItem*> &items = selectionSet->items();
    GraphicsViewManager::instance()->updateSelection(items);
    IEditor *editor = IEditor::instance();
    ISelectionSet *track_ss = editor->currentSelection(TrackItem);
    ISelectionSet *note_ss = editor->currentSelection(NoteItem);
    foreach (IGraphicsItem *item, items) {
        IModelItem *model_item = query<IModelItem>(item);
        if (model_item->isTypeOfItem(TrackItem))
            track_ss->append(item);
        else if (model_item->isTypeOfItem(NoteItem))
            note_ss->append(item);
    }
}

}
