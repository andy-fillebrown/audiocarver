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

#include "ac_gui_model_editorupdater.h"
#include <ieditor.h>

namespace Model {

EditorUpdater::EditorUpdater()
    :   Base::ModelWatcher(ISession::instance())
{}

void EditorUpdater::beginChangeData(IModelItem *item, int role)
{
    IEditor::instance()->beginChangeData(item, role);
}

void EditorUpdater::endChangeData(IModelItem *item, int role)
{
    IEditor::instance()->endChangeData(item, role);
}

void EditorUpdater::endInsertItem(IModelItem *list, int index)
{
    IEditor::instance()->endInsertItem(list, index);
}

void EditorUpdater::endRemoveItem(IModelItem *list, int index)
{
    IEditor::instance()->endRemoveItem(list, index);
}

}
