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

#ifndef MI_GUI_UNDO_LISTCOMMAND_H
#define MI_GUI_UNDO_LISTCOMMAND_H

#include "mi_gui_undo_modelitemcommand.h"

namespace Undo {

class ListCommand : public ModelItemCommand
{
    IModelItem *_list;
    int _index;
    uint _deleteItem : 1;

public:
    ListCommand(IModelItem *list, int index, QUndoCommand *parent = 0)
        :   ModelItemCommand(0, parent)
        ,   _list(list)
        ,   _index(index)
        ,   _deleteItem(false)
    {}

    ~ListCommand();

    IModelItem *list() const
    {
        return _list;
    }

    int index() const
    {
        return _index;
    }

    void insert();
    void remove();
};

}

#endif
