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

#ifndef MI_GUI_UNDO_DATACHANGECOMMAND_H
#define MI_GUI_UNDO_DATACHANGECOMMAND_H

#include "mi_gui_undo_modelitemcommand.h"
#include <QVariant>

namespace Undo {

class DataChangeCommand : public ModelItemCommand
{
    int _role;
    QVariant _oldData;
    QVariant _newData;

public:
    DataChangeCommand(IModelItem *item, int role, QUndoCommand *parent = 0);

    int id() const;
    void redo();
    void undo();
    void updateNewData();
};

}

#endif
