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

#include "mi_gui_undo_listcommand.h"
#include <iaggregate.h>
#include <imodelitem.h>

namespace Undo {

ListCommand::~ListCommand()
{
    if (_deleteItem) {
        IModelItem *item = this->item();
        delete query<IAggregate>(item);
    }
}

void ListCommand::insert()
{
    _deleteItem = false;
    if (!isEnabled()) {
        enable();
        return;
    }
    _list->insertItem(_index, item());
}

void ListCommand::remove()
{
    _deleteItem = true;
    if (!isEnabled()) {
        enable();
        return;
    }
    _list->removeItemAt(_index);
}

}
