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
#include <iaggregate.h>
#include <idatabase.h>
#include <ieditor.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iundomanager.h>

static Undo::Stack *instance = 0;

static bool notOkToUndo()
{
    IUndoManager *undo_manager = IUndoManager::instance();
    return IDatabase::instance()->isReading()
            || undo_manager->isPaused()
            || undo_manager->isUndoing();
}

namespace Undo {

Stack *Stack::instance()
{
    return ::instance;
}

Stack::Stack(QObject *parent)
    :   QUndoStack(parent)
    ,   _command(0)
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
    qDelete(_command);
    foreach (IModelItem *orphaned_item, _orphanedItems)
        delete query<IAggregate>(orphaned_item);
    _orphanedItems.clear();
}

void Stack::beginCommand()
{
    if (_command)
        return;
    _command = new QUndoCommand;
}

void Stack::endCommand()
{
    if (!_command)
        return;
    push(_command);
    _command = 0;
}

void Stack::dataAboutToBeChanged(IModelItem *item, int role)
{
    if (notOkToUndo())
        return;
    _dataChanges.append(new DataChangeCommand(item, role, _command));
}

void Stack::dataChanged(IModelItem *item, int role)
{
    if (notOkToUndo())
        return;
    const int n = _dataChanges.count();
    for (int i = 0;  i < n;  ++i) {
        DataChangeCommand *cmd = _dataChanges.at(i);
        if (item != cmd->item())
            continue;
        cmd->updateNewData();
        _dataChanges.removeAt(i);
        --i;
        if (!_command)
            push(cmd);
        break;
    }
}

void Stack::itemAboutToBeInserted(IModelItem *list, int index)
{
    if (notOkToUndo())
        return;
    _inserts.append(new InsertCommand(list, index, _command));
}

void Stack::itemInserted(IModelItem *list, int index)
{
    if (notOkToUndo())
        return;
    const int n = _inserts.count();
    for (int i = 0;  i < n;  ++i) {
        InsertCommand *cmd = _inserts.at(i);
        IModelItem *item = list->itemAt(index);
        cmd->setItem(item);
        if (list != cmd->list() || index != cmd->index())
            continue;
        _inserts.removeAt(i);
        if (!_command)
            push(cmd);
        _orphanedItems.removeAll(item);
        break;
    }
}

void Stack::itemAboutToBeRemoved(IModelItem *list, int index)
{
    if (notOkToUndo())
        return;
    RemoveCommand *cmd = new RemoveCommand(list, index, _command);
    cmd->setItem(list->itemAt(index));
    _removes.append(cmd);
}

void Stack::itemRemoved(IModelItem *list, int index)
{
    if (notOkToUndo())
        return;
    const int n = _removes.count();
    for (int i = 0;  i < n;  ++i) {
        RemoveCommand *cmd = _removes.at(i);
        if (list != cmd->list() || index != cmd->index())
            continue;
        _removes.removeAt(i);
        if (!_command)
            push(cmd);
        _orphanedItems.append(cmd->item());
        break;
    }
}

void Stack::modelReset()
{
    clear();
}

}
