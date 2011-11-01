/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "ac_editor.h"

#include <ac_undo.h>

#include <ac_model.h>

#include <mi_idatabase.h>

class EditorPrivate
{
public:
    Editor *q;
    Model *model;
    UndoStack *undoStack;
    quint32 undoing : 32;

    EditorPrivate(Editor *q)
        :   q(q)
        ,   model(qobject_cast<Model*>(IDatabase::instance()->model()))
        ,   undoStack(0)
        ,   undoing(false)
    {}

    void init()
    {
        undoStack = new UndoStack(q);
    }
};

Editor::Editor()
    :   d(new EditorPrivate(this))
{
    d->init();
}

Editor::~Editor()
{
    delete d;
}

void Editor::undo()
{
    if (d->undoStack->canUndo()) {
        d->undoing = true;
        d->undoStack->undo();
        d->undoing = false;
    }
}

void Editor::redo()
{
    if (d->undoStack->canRedo()) {
        d->undoing = true;
        d->undoStack->redo();
        d->undoing = false;
    }
}

void Editor::cut()
{
}

void Editor::copy() const
{
}

void Editor::paste()
{
}

void Editor::selectAll()
{
}

void Editor::beginCommand(const QString &text)
{
    d->undoStack->beginMacro(text);
}

void Editor::pushCommand(QUndoCommand *cmd)
{
    if (!d->undoing)
        d->undoStack->push(cmd);
    else
        delete cmd;
}

void Editor::endCommand()
{
    d->undoStack->endMacro();
}
