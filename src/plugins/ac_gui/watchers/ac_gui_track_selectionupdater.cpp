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

#include "ac_gui_track_selectionupdater.h"
#include "ac_gui_selecteditemspropertymodel.h"
#include "ac_gui_trackview.h"
#include <igraphicsitem.h>
#include <iselectionset.h>

namespace Track {

void SelectionUpdater::endChangeSelection(ISelectionSet *selectionSet)
{
    const QList<IGraphicsItem*> &items = selectionSet->items();
    if (items.isEmpty()) {
        TrackView *track_view = TrackView::instance();
        QItemSelectionModel *ss_model = track_view->selectionModel();
        ss_model->clearSelection();
    }
    SelectedItemsPropertyModel::instance()->update();
}

}
