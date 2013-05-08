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

#include "ac_gui_editor.h"
#include "ac_gui_object_selectionupdater.h"
#include "ac_gui_selectionset.h"
#include "ac_gui_track_selectionupdater.h"
#include <ac_core_namespace.h>
#include <mi_core_base_aggregate.h>

#include <QtDebug>

using namespace Mi;

namespace Ac {
namespace Gui {

Editor::Editor()
{
    _objectSS = new Base::Aggregate;
    new SelectionSet(_objectSS);
    new Object::SelectionUpdater(_objectSS);
    _trackSS = new Base::Aggregate;
    new SelectionSet(_trackSS);
    new Track::SelectionUpdater(_trackSS);
    _noteSS = new Base::Aggregate;
    new SelectionSet(_noteSS);
}

Editor::~Editor()
{
    qDelete(_noteSS);
    qDelete(_trackSS);
    qDelete(_objectSS);
}

ISelectionSet *Editor::currentSelection(int itemType) const
{
    switch (itemType) {
    case UnknownItem:
        return query<ISelectionSet>(_objectSS);
    case TrackItem:
        return query<ISelectionSet>(_trackSS);
    case NoteItem:
        return query<ISelectionSet>(_noteSS);
    default:
        Q_ASSERT(false);
        return 0;
    }
}

void Editor::cut()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::copy() const
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::paste()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::selectAll()
{
    qDebug() << Q_FUNC_INFO;
}

}
}
