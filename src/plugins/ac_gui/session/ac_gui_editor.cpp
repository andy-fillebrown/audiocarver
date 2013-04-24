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
#include "ac_gui_selectionset.h"
#include "ac_gui_selectionupdater.h"
#include <mi_core_base_aggregate.h>
#include <iselectionset.h>
#include <QtDebug>

namespace Gui {

Editor::Editor()
{
    _ss = new Base::Aggregate;
    new SelectionSet(_ss);
    new SelectionUpdater(_ss);
}

Editor::~Editor()
{
    delete _ss;
}

ISelectionSet *Editor::currentSelection() const
{
    return query<ISelectionSet>(_ss);
}

void Editor::undo()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::redo()
{
    qDebug() << Q_FUNC_INFO;
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
