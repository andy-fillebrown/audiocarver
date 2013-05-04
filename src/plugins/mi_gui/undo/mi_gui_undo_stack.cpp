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
#include <idatabase.h>
#include <ieditor.h>
#include <imodel.h>

namespace Undo {

Stack::Stack(QObject *parent)
    :   QUndoStack(parent)
{
    IModel *model = IModel::instance();
    connect(model, SIGNAL(dataAboutToBeChanged(const IModelItem*,int)), SLOT(dataAboutToBeChanged(const IModelItem*,int)));
    connect(model, SIGNAL(dataChanged(const IModelItem*,int)), SLOT(dataAboutToBeChanged(const IModelItem*,int)));
    connect(model, SIGNAL(itemAboutToBeInserted(const IModelItem*,int)), SLOT(itemAboutToBeInserted(const IModelItem*,int)));
    connect(model, SIGNAL(itemInserted(const IModelItem*,int)), SLOT(itemInserted(const IModelItem*,int)));
    connect(model, SIGNAL(itemAboutToBeRemoved(const IModelItem*,int)), SLOT(itemAboutToBeRemoved(const IModelItem*,int)));
    connect(model, SIGNAL(itemRemoved(const IModelItem*,int)), SLOT(itemRemoved(const IModelItem*,int)));
    connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
}

void Stack::dataAboutToBeChanged(IModelItem *item, int role)
{
    IEditor *editor = IEditor::instance();
    if (IDatabase::instance()->isReading()
            || editor->isUndoing()
            || editor->isCreating())
        return;
    _dataChanges.append(new DataChangeCommand(item, role));
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
        push(cmd);
        break;
    }
}

void Stack::itemAboutToBeInserted(IModelItem *list, int index)
{
//    if (undoCommandActive || IDatabase::instance()->isReading())
//        return;
//    d->inserts.append(new UndoInsertCommand(start, query<IModelList>(query<IModel>(IDatabase::instance())->itemFromIndex(parent))));
}

void Stack::itemInserted(IModelItem *list, int index)
{
//    IDatabase *db = IDatabase::instance();
//    if (undoCommandActive
//            || db->isReading()
//            || IEditor::instance()->isCreating())
//        return;
//    IModel *model = query<IModel>(db);
//    const int n = d->inserts.count();
//    for (int i = 0;  i < n;  ++i) {
//        UndoInsertCommand *cmd = d->inserts.at(i);
//        if (query<IModelList>(model->itemFromIndex(parent)) != cmd->list() || start != cmd->row())
//            continue;
//        d->inserts.removeAt(i);
//        push(cmd);
//        cmd->setItem(model->itemFromIndex(query<IQModel>(db)->index(start, 0, parent)));
//        break;
//    }
}

void Stack::itemAboutToBeRemoved(IModelItem *list, int index)
{
//    IDatabase *db = IDatabase::instance();
//    if (undoCommandActive
//            || IDatabase::instance()->isReading()
//            || IEditor::instance()->isCreating())
//        return;
//    IModel *model = query<IModel>(db);
//    IModelList *list = query<IModelList>(model->itemFromIndex(parent));
//    IModelItem *item = list->at(start);
//    d->removes.append(new UndoRemoveCommand(item, start, list));
}

void Stack::itemRemoved(IModelItem *list, int index)
{
//    IDatabase *db = IDatabase::instance();
//    if (undoCommandActive
//            || IDatabase::instance()->isReading()
//            || IEditor::instance()->isCreating())
//        return;
//    IModelList *list = query<IModelList>(query<IModel>(db)->itemFromIndex(parent));
//    const int n = d->removes.count();
//    for (int i = 0;  i < n;  ++i) {
//        UndoRemoveCommand *cmd = d->removes.at(i);
//        if (list != cmd->list() || start != cmd->row())
//            continue;
//        d->removes.removeAt(i);
//        push(cmd);
//        break;
//    }
}

void Stack::modelReset()
{
    clear();
}

}
