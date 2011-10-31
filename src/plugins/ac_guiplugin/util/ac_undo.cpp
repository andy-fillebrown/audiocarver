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

#include <ac_model.h>

#include <mi_idatabase.h>

class UndoCommandPrivate
{
public:
    IModelItem *item;

    UndoCommandPrivate(IModelItem *item)
        :   item(item)
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

class UndoDataCommandPrivate : public UndoCommandPrivate
{
public:
    QMap<int, QVariant> oldData;
    QMap<int, QVariant> newData;

    UndoDataCommandPrivate(IModelItem *item)
        :   UndoCommandPrivate(item)
    {}
};

UndoDataCommand::UndoDataCommand(IModelItem *item, QUndoCommand *parent)
    :   UndoCommand(*(new UndoDataCommandPrivate(item)), parent)
{}

void UndoDataCommand::updateNewData()
{
}

void UndoDataCommand::redo()
{
}

void UndoDataCommand::undo()
{
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
};

UndoListCommand::UndoListCommand(UndoListCommandPrivate &dd, QUndoCommand *parent)
    :   UndoCommand(dd, parent)
{}

UndoListCommand::~UndoListCommand()
{
}

void UndoListCommand::insert()
{
}

void UndoListCommand::remove()
{
    Q_D(UndoListCommand);
    d->model()->takeItem(d->row, d->parentIndex);
    d->deleteItem = true;
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

    UndoStackPrivate(UndoStack *q)
        :   q(q)
        ,   model(qobject_cast<Model*>(IDatabase::instance()->model()))
    {}
};

UndoStack::UndoStack(QObject *parent)
    :   QUndoStack(parent)
    ,   d(new UndoStackPrivate(this))
{
    Model *model = qobject_cast<Model*>(IDatabase::instance()->model());
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

void UndoStack::dataAboutToBeChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);
}

void UndoStack::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);
}

void UndoStack::modelReset()
{
}

void UndoStack::rowsAboutToBeInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
}

void UndoStack::rowsInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
}

void UndoStack::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
}

void UndoStack::rowsRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
}
