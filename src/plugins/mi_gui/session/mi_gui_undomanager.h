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

#ifndef MI_GUI_UNDOMANAGER_H
#define MI_GUI_UNDOMANAGER_H

#include "mi_gui_base_undomanager.h"

namespace Undo {
class Stack;
}

namespace Mi {
namespace Gui {

class MI_GUI_EXPORT UndoManager : public Base::UndoManager
{
    Undo::Stack *_undoStack;
    uint _undoing : 1;
    uint _paused : 1;
    uint _inCommand : 1;

public:
    UndoManager();

protected:
    ~UndoManager();

    void setUndoStack(Undo::Stack *stack);

    void reset();

    bool isUndoing() const
    {
        return _undoing;
    }

    void undo();
    void redo();

    bool isPaused() const
    {
        return _paused;
    }

    void pause();
    void resume();

    bool isInCommand() const
    {
        return _inCommand;
    }

    void beginCommand();
    void endCommand();
};

}
}

#endif
