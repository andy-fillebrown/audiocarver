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

#include "ac_gui_undomanager.h"
#include "ac_gui_namespace.h"
#include "ac_gui_undo_stack.h"
#include "ac_gui_undo_viewsettingscommand.h"

using namespace Undo;

namespace Ac {
namespace Gui {

UndoManager::UndoManager()
{
    setUndoStack(new Ac::Undo::Stack);
}

void UndoManager::pushCommand(int commandId)
{
    if (UndoViewSettingsCommand == commandId)
        Stack::instance()->push(new ViewSettingsCommand);
    else
        Mi::Gui::UndoManager::pushCommand(commandId);
}

}
}
