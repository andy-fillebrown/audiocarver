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

#include "mi_gui_undomanager.h"
#include "mi_gui_undo_stack.h"

namespace Mi {
namespace Gui {

UndoManager::UndoManager()
    :   _undoStack(new Undo::Stack)
    ,   _undoing(false)
    ,   _paused(false)
    ,   _inCommand(false)
{
}

UndoManager::~UndoManager()
{
    qDelete(_undoStack);
}

void UndoManager::setUndoStack(Undo::Stack *stack)
{
    if (_undoStack == stack)
        return;
    qDelete(_undoStack);
    _undoStack = stack;
}

void UndoManager::reset()
{
    _undoStack->clear();
}

void UndoManager::undo()
{
    _undoing = true;
    _undoStack->undo();
    _undoing = false;
}

void UndoManager::redo()
{
    _undoing = true;
    _undoStack->redo();
    _undoing = false;
}

void UndoManager::pause()
{
    _paused = true;
}

void UndoManager::resume()
{
    _paused = false;
}

void UndoManager::beginCommand()
{
    _inCommand = true;
    _undoStack->beginCommand();
}

void UndoManager::endCommand()
{
    _undoStack->endCommand();
    _inCommand = false;
}

}
}
