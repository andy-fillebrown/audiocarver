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

#include "ac_undo.h"

#include <ac_imodelitem.h>
#include <ac_model.h>

#include <mi_idatabase.h>

static bool undoCommandActive = false;
static bool databaseReading = false;

class UndoCommandPrivate
{
public:
    IModelItem *item;
    quint32 enabled : 32;

    UndoCommandPrivate(IModelItem *item)
        :   item(item)
        ,   enabled(false)
    {}

    virtual ~UndoCommandPrivate()
    {}

    Model *model() const
    {
        return qobject_cast<Model*>(IDatabase::instance()->model());
    }
};

UndoCommand::~UndoCommand()
{
    delete d_ptr;
}

IModelItem *UndoCommand::item() const
{
    return d_ptr->item;
}

void UndoCommand::enable()
{
    d_ptr->enabled = true;
}

class UndoDataCommandPrivate : public UndoCommandPrivate
{
public:
    QMap<int, QVariant> oldData;
    QMap<int, QVariant> newData;

    UndoDataCommandPrivate(IModelItem *item)
        :   UndoCommandPrivate(item)
    {}

    QMap<int, QVariant> data() const
    {
        QMap<int, QVariant> map;
        const int n = item->persistentRoleCount();
        for (int i = 0;  i < n;  ++i) {
            const int role = item->persistentRoleAt(i);
            const QVariant data = item->data(role);
            map.insert(role, data);
        }
        return map;
    }

    void setData(const QMap<int, QVariant> &data)
    {
        const QList<int> keys = data.keys();
        const int n = keys.count();
        for (int i = 0;  i < n;  ++i) {
            const int &role = keys.at(i);
            item->setData(data.value(role), role);
        }
    }
};

UndoDataCommand::UndoDataCommand(IModelItem *item, QUndoCommand *parent)
    :   UndoCommand(*(new UndoDataCommandPrivate(item)), parent)
{
    Q_D(UndoDataCommand);
    d->oldData = d->data();
}

void UndoDataCommand::updateNewData()
{
    Q_D(UndoDataCommand);
    d->newData = d->data();
}

void UndoDataCommand::redo()
{
    if (!d_ptr->enabled)
        return;
    Q_D(UndoDataCommand);
    undoCommandActive = true;
    d->setData(d->newData);
    undoCommandActive = false;
}

void UndoDataCommand::undo()
{
    if (!d_ptr->enabled)
        return;
    Q_D(UndoDataCommand);
    undoCommandActive = true;
    d->setData(d->oldData);
    undoCommandActive = false;
}

class UndoListCommandPrivate : public UndoCommandPrivate
{
public:
    int row;
    QModelIndex parentIndex;
    quint32 deleteItem : 32;

    UndoListCommandPrivate(IModelItem *item, int row, const QModelIndex &parentIndex)
        :   UndoCommandPrivate(item)
        ,   row(row)
        ,   parentIndex(parentIndex)
        ,   deleteItem(false)
    {}

    ~UndoListCommandPrivate()
    {
        if (deleteItem)
            delete item;
    }
};

UndoListCommand::UndoListCommand(UndoListCommandPrivate &dd, QUndoCommand *parent)
    :   UndoCommand(dd, parent)
{}

UndoListCommand::~UndoListCommand()
{
}

void UndoListCommand::insert()
{
    if (!d_ptr->enabled)
        return;
    Q_D(UndoListCommand);
    undoCommandActive = true;
    d->model()->insertItem(item(), d->row, d->parentIndex);
    d->deleteItem = false;
    undoCommandActive = false;
}

void UndoListCommand::remove()
{
    if (!d_ptr->enabled)
        return;
    Q_D(UndoListCommand);
    undoCommandActive = true;
    d->model()->takeItem(d->row, d->parentIndex);
    d->deleteItem = true;
    undoCommandActive = false;
}

bool UndoListCommand::mergeWith(const QUndoCommand *other)
{
    Q_UNUSED(other);
    return false;
}

UndoInsertCommand::UndoInsertCommand(IModelItem *item, int row, const QModelIndex &parentIndex, QUndoCommand *parent)
    :   UndoListCommand(*(new UndoListCommandPrivate(item, row, parentIndex)), parent)
{}

UndoRemoveCommand::UndoRemoveCommand(IModelItem *item, int row, const QModelIndex &parentIndex, QUndoCommand *parent)
    :   UndoListCommand(*(new UndoListCommandPrivate(item, row, parentIndex)), parent)
{}

class UndoStackPrivate
{
public:
    UndoStack *q;
    Model *model;
    QList<UndoDataCommand*> dataChanges;
    QList<UndoInsertCommand*> inserts;
    QList<UndoRemoveCommand*> removes;

    UndoStackPrivate(UndoStack *q)
        :   q(q)
        ,   model(qobject_cast<Model*>(IDatabase::instance()->model()))
    {}
};

UndoStack::UndoStack(QObject *parent)
    :   QUndoStack(parent)
    ,   d(new UndoStackPrivate(this))
{
    IDatabase *db = IDatabase::instance();
    connect(db, SIGNAL(databaseAboutToBeRead()), SLOT(databaseAboutToBeRead()));
    connect(db, SIGNAL(databaseRead()), SLOT(databaseRead()));

    Model *model = qobject_cast<Model*>(db->model());
    connect(model, SIGNAL(dataAboutToBeChanged(QModelIndex,QModelIndex)), SLOT(dataAboutToBeChanged(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
    connect(model, SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)), SLOT(rowsAboutToBeInserted(QModelIndex,int,int)));
    connect(model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(rowsInserted(QModelIndex,int,int)));
    connect(model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)), SLOT(rowsAboutToBeRemoved(QModelIndex,int,int)));
    connect(model, SIGNAL(rowsRemoved(QModelIndex,int,int)), SLOT(rowsRemoved(QModelIndex,int,int)));
}

UndoStack::~UndoStack()
{
    delete d;
}

void UndoStack::databaseAboutToBeRead()
{
    databaseReading = true;
}

void UndoStack::databaseRead()
{
    databaseReading = false;
}

void UndoStack::dataAboutToBeChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);
    if (undoCommandActive || databaseReading)
        return;
    d->dataChanges.append(new UndoDataCommand(d->model->itemFromIndex(topLeft)));
}

void UndoStack::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);
    if (undoCommandActive || databaseReading)
        return;
    IModelItem *item = d->model->itemFromIndex(topLeft);
    const int n = d->dataChanges.count();
    for (int i = 0;  i < n;  ++i) {
        UndoDataCommand *cmd = d->dataChanges.at(i);
        if (item != cmd->item())
            continue;
        cmd->updateNewData();
        d->dataChanges.removeAt(i);
        push(cmd);
        cmd->enable();
        break;
    }
}

void UndoStack::modelReset()
{
    clear();
}

void UndoStack::rowsAboutToBeInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(end);
    if (undoCommandActive || databaseReading)
        return;
    d->inserts.append(new UndoInsertCommand(d->model->itemFromIndex(d->model->index(start, parent)), start, parent));
}

void UndoStack::rowsInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(end);
    if (undoCommandActive || databaseReading)
        return;
    IModelItem *item = d->model->itemFromIndex(d->model->index(start, parent));
    const int n = d->inserts.count();
    for (int i = 0;  i < n;  ++i) {
        UndoInsertCommand *cmd = d->inserts.at(i);
        if (item != cmd->item())
            continue;
        d->inserts.removeAt(i);
        push(cmd);
        cmd->enable();
        break;
    }
}

void UndoStack::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(end);
    if (undoCommandActive || databaseReading)
        return;
    d->removes.append(new UndoRemoveCommand(d->model->itemFromIndex(d->model->index(start, parent)), start, parent));
}

void UndoStack::rowsRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(end);
    if (undoCommandActive || databaseReading)
        return;
    IModelItem *item = d->model->itemFromIndex(d->model->index(start, parent));
    const int n = d->removes.count();
    for (int i = 0;  i < n;  ++i) {
        UndoRemoveCommand *cmd = d->removes.at(i);
        if (item != cmd->item())
            continue;
        d->removes.removeAt(i);
        push(cmd);
        cmd->enable();
        break;
    }
}
