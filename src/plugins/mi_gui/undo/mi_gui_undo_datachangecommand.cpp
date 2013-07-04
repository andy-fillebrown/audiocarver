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

#include "mi_gui_undo_datachangecommand.h"
#include "mi_gui_namespace.h"
#include <imodelitem.h>

using namespace Mi;

namespace Undo {

DataChangeCommand::DataChangeCommand(IModelItem *item, int role, QUndoCommand *parent)
    :   ModelItemCommand(item, parent)
    ,   _role(role)
    ,   _oldData(item->getValue(_role))
{}

int DataChangeCommand::id() const
{
    return UndoDataChangeCommand;
}

void DataChangeCommand::redo()
{
    if (!isEnabled()) {
        enable();
        return;
    }
    item()->setValue(_role, _newData);
}

void DataChangeCommand::undo()
{
    item()->setValue(_role, _oldData);
}

void DataChangeCommand::updateNewData()
{
    _newData = item()->getValue(_role);
}

}
