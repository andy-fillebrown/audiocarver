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

#include "mi_gui_undo_stack.h"
#include "mi_gui_undo_datachangecommand.h"
#include "mi_gui_undo_insertcommand.h"
#include "mi_gui_undo_removecommand.h"
#include <idatabase.h>
#include <ieditor.h>
#include <imodel.h>
#include <imodelitem.h>

Undo::Stack *instance = 0;

namespace Undo {

Stack *Stack::instance()
{
    return ::instance;
}

Stack::Stack(QObject *parent)
    :   QUndoStack(parent)
{
    IModel *model = IModel::instance();
    connect(model, SIGNAL(dataAboutToBeChanged(IModelItem*,int)), SLOT(dataAboutToBeChanged(IModelItem*,int)));
    connect(model, SIGNAL(dataChanged(IModelItem*,int)), SLOT(dataChanged(IModelItem*,int)));
    connect(model, SIGNAL(itemAboutToBeInserted(IModelItem*,int)), SLOT(itemAboutToBeInserted(IModelItem*,int)));
    connect(model, SIGNAL(itemInserted(IModelItem*,int)), SLOT(itemInserted(IModelItem*,int)));
    connect(model, SIGNAL(itemAboutToBeRemoved(IModelItem*,int)), SLOT(itemAboutToBeRemoved(IModelItem*,int)));
    connect(model, SIGNAL(itemRemoved(IModelItem*,int)), SLOT(itemRemoved(IModelItem*,int)));
    connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
    ::instance = this;
}

Stack::~Stack()
{
    ::instance = 0;
}

void Stack::dataAboutToBeChanged(IModelItem *item, int role)
{
    IEditor *editor = IEditor::instance();
    if (IDatabase::instance()->isReading()
            || editor->isUndoing()
            || editor->isCreating())
        return;
    _dataChanges.append(new DataChangeCommand(item, role, IEditor::instance()->currentCommand()));
}

void Stack::dataChanged(IModelItem *item, int role)
{
    IEditor *editor = IEditor::instance();
    if (IDatabase::instance()->isReading()
            || editor->isUndoing()
            || editor->isCreating())
        return;
    const int n = _dataChanges.count();
    for (int i = 0;  i < n;  ++i) {
        DataChangeCommand *cmd = _dataChanges.at(i);
        if (item != cmd->item())
            continue;
        cmd->updateNewData();
        _dataChanges.removeAt(i);
        --i;
        if (!IEditor::instance()->isInCommand())
            push(cmd);
        break;
    }
}

void Stack::itemAboutToBeInserted(IModelItem *list, int index)
{
    IEditor *editor = IEditor::instance();
    if (IDatabase::instance()->isReading()
            || editor->isUndoing()
            || editor->isCreating())
        return;
    _inserts.append(new InsertCommand(list, index, editor->currentCommand()));
}

void Stack::itemInserted(IModelItem *list, int index)
{
    IEditor *editor = IEditor::instance();
    if (IDatabase::instance()->isReading()
            || editor->isUndoing()
            || editor->isCreating())
        return;
    const int n = _inserts.count();
    for (int i = 0;  i < n;  ++i) {
        InsertCommand *cmd = _inserts.at(i);
        cmd->setItem(list->itemAt(index));
        if (list != cmd->list() || index != cmd->index())
            continue;
        _inserts.removeAt(i);
        if (!editor->isInCommand())
            push(cmd);
        break;
    }
}

void Stack::itemAboutToBeRemoved(IModelItem *list, int index)
{
    IEditor *editor = IEditor::instance();
    if (IDatabase::instance()->isReading()
            || editor->isUndoing()
            || editor->isCreating())
        return;
    RemoveCommand *cmd = new RemoveCommand(list, index, editor->currentCommand());
    cmd->setItem(list->itemAt(index));
    _removes.append(cmd);
}

void Stack::itemRemoved(IModelItem *list, int index)
{
    IEditor *editor = IEditor::instance();
    if (IDatabase::instance()->isReading()
            || editor->isUndoing()
            || editor->isCreating())
        return;
    const int n = _removes.count();
    for (int i = 0;  i < n;  ++i) {
        RemoveCommand *cmd = _removes.at(i);
        if (list != cmd->list() || index != cmd->index())
            continue;
        _removes.removeAt(i);
        if (!editor->isInCommand())
            push(cmd);
        break;
    }
}

void Stack::modelReset()
{
    clear();
}

}
