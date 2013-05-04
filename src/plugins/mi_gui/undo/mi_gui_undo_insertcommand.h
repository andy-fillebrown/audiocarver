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

#ifndef MI_GUI_UNDO_INSERTCOMMAND_H
#define MI_GUI_UNDO_INSERTCOMMAND_H

#include "mi_gui_undo_listcommand.h"

namespace Undo {

class InsertCommand : public ListCommand
{
public:
    InsertCommand(IModelItem *list, int index, QUndoCommand *parent = 0)
        :   ListCommand(0, index, parent)
    {}

    int id() const;

    void redo()
    {
        insert();
    }

    void undo()
    {
        remove();
    }
};

}

#endif
