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

    EditorPrivate(Editor *q)
        :   q(q)
        ,   model(qobject_cast<Model*>(IDatabase::instance()->model()))
        ,   undoStack(0)
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
    d->undoStack->undo();
}

void Editor::redo()
{
    d->undoStack->redo();
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
