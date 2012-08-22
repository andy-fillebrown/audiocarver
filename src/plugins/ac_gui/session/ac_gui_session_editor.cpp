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

#include "ac_gui_editor.h"

#include <ac_igraphicsviewgroup.h>

namespace Ac {
namespace Gui {

IAggregator *Editor::init()
{
    return Mi::Gui::Editor::init();
}

Editor::~Editor()
{
    qDeleteAll(_viewGroups);
    _viewGroups.clear();
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

IAggregate *ViewManager::init()
{
    return this;
}

} // namespace Gui
} // namespace Ac
