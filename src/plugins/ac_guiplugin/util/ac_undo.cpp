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

#include <ac_viewmanager.h>

#include <ac_model.h>

#include <mi_ieditor.h>

#include <mi_idatabase.h>
#include <mi_imodelitem.h>

static bool undoCommandActive = false;
static bool databaseReading = false;

class UndoCommandPrivate
{
    quint32 enabled : 32;

public:
    UndoCommandPrivate()
        :   enabled(false)
    {}

    virtual ~UndoCommandPrivate()
    {}

    bool isEnabled() const
    {
        return enabled;
    }

    void enable()
    {
        enabled = true;
    }
};

UndoCommand::~UndoCommand()
{
    delete d_ptr;
}

class UndoViewSettingsCommandPrivate : public UndoCommandPrivate
{
public:
    qreal oldTimePos;
    qreal oldPitchPos;
    qreal oldControlPos;
    qreal oldTimeScale;
    qreal oldPitchScale;
    qreal oldControlScale;
    qreal newTimePos;
    qreal newPitchPos;
    qreal newControlPos;
    qreal newTimeScale;
    qreal newPitchScale;
    qreal newControlScale;

    UndoViewSettingsCommandPrivate()
    {
        ViewManager *vm = ViewManager::instance();
        oldTimePos = vm->position(Ac::TimePositionRole);
        oldPitchPos = vm->position(Ac::PitchPositionRole);
        oldControlPos = vm->position(Ac::ControlPositionRole);
        oldTimeScale = vm->scale(Ac::TimeScaleRole);
        oldPitchScale = vm->scale(Ac::PitchScaleRole);
        oldControlScale = vm->scale(Ac::ControlScaleRole);
    }

    void updateNewData()
    {
        ViewManager *vm = ViewManager::instance();
        newTimePos = vm->position(Ac::TimePositionRole);
        newPitchPos = vm->position(Ac::PitchPositionRole);
        newControlPos = vm->position(Ac::ControlPositionRole);
        newTimeScale = vm->scale(Ac::TimeScaleRole);
        newPitchScale = vm->scale(Ac::PitchScaleRole);
        newControlScale = vm->scale(Ac::ControlScaleRole);
    }
};

UndoViewSettingsCommand::UndoViewSettingsCommand(QUndoCommand *parent)
    :   UndoCommand(*(new UndoViewSettingsCommandPrivate), parent)
{}

bool UndoViewSettingsCommand::mergeWith(const QUndoCommand *other)
{
    if (Ac::UndoViewSettingsCommandId != other->id()) {
        return false;
    }
    Q_D(UndoViewSettingsCommand);
    d->updateNewData();
    return true;
}

void UndoViewSettingsCommand::redo()
{
    Q_D(UndoViewSettingsCommand);
    if (!d->isEnabled()) {
        d->updateNewData();
        d->enable();
        return;
    }
    ViewManager *vm = ViewManager::instance();
    vm->setPosition(d->newTimePos, Ac::TimePositionRole);
    vm->setPosition(d->newPitchPos, Ac::PitchPositionRole);
    vm->setPosition(d->newControlPos, Ac::ControlPositionRole);
    vm->setScale(d->newTimeScale, Ac::TimeScaleRole);
    vm->setScale(d->newPitchScale, Ac::PitchScaleRole);
    vm->setScale(d->newControlScale, Ac::ControlScaleRole);
    vm->updateViews();
}

void UndoViewSettingsCommand::undo()
{
    Q_D(UndoViewSettingsCommand);
    ViewManager *vm = ViewManager::instance();
    vm->setPosition(d->oldTimePos, Ac::TimePositionRole);
    vm->setPosition(d->oldPitchPos, Ac::PitchPositionRole);
    vm->setPosition(d->oldControlPos, Ac::ControlPositionRole);
    vm->setScale(d->oldTimeScale, Ac::TimeScaleRole);
    vm->setScale(d->oldPitchScale, Ac::PitchScaleRole);
    vm->setScale(d->oldControlScale, Ac::ControlScaleRole);
    vm->updateViews();
}

class UndoModelItemCommandPrivate : public UndoCommandPrivate
{
public:
    IModelItem *item;

    UndoModelItemCommandPrivate(IModelItem *item = 0)
        :   item(item)
    {}

    IModel *model() const
    {
        return IDatabase::instance()->model();
    }
};

UndoModelItemCommand::UndoModelItemCommand(UndoModelItemCommandPrivate &dd, QUndoCommand *parent)
    :   UndoCommand(dd, parent)
{}

IModelItem *UndoModelItemCommand::item() const
{
    Q_D(const UndoModelItemCommand);
    return d->item;
}

void UndoModelItemCommand::setItem(IModelItem *item)
{
    Q_D(UndoModelItemCommand);
    d->item = item;
}

class UndoDataCommandPrivate : public UndoModelItemCommandPrivate
{
public:
    QMap<int, QVariant> oldData;
    QMap<int, QVariant> newData;

    UndoDataCommandPrivate(IModelItem *item)
        :   UndoModelItemCommandPrivate(item)
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
    :   UndoModelItemCommand(*(new UndoDataCommandPrivate(item)), parent)
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
    Q_D(UndoDataCommand);
    if (!d->isEnabled()) {
        d->enable();
        return;
    }
    undoCommandActive = true;
    d->setData(d->newData);
    undoCommandActive = false;
}

void UndoDataCommand::undo()
{
    Q_D(UndoDataCommand);
    undoCommandActive = true;
    d->setData(d->oldData);
    undoCommandActive = false;
}

class UndoListCommandPrivate : public UndoModelItemCommandPrivate
{
public:
    int row;
    QModelIndex parentIndex;

    UndoListCommandPrivate(int row, const QModelIndex &parentIndex)
        :   row(row)
        ,   parentIndex(parentIndex)
    {}

    UndoListCommandPrivate(IModelItem *item, int row, const QModelIndex &parentIndex)
        :   UndoModelItemCommandPrivate(item)
        ,   row(row)
        ,   parentIndex(parentIndex)
    {}

    ~UndoListCommandPrivate()
    {}
};

UndoListCommand::UndoListCommand(UndoListCommandPrivate &dd, QUndoCommand *parent)
    :   UndoModelItemCommand(dd, parent)
{}

const QModelIndex &UndoListCommand::parentIndex() const
{
    Q_D(const UndoListCommand);
    return d->parentIndex;
}

int UndoListCommand::row() const
{
    Q_D(const UndoListCommand);
    return d->row;
}

void UndoListCommand::insert()
{
    Q_D(UndoListCommand);
    if (!d->isEnabled()) {
        d->enable();
        return;
    }
    undoCommandActive = true;
    d->model()->insertItem(item(), d->row, d->parentIndex);
    undoCommandActive = false;
}

void UndoListCommand::remove()
{
    Q_D(UndoListCommand);
    if (!d->isEnabled()) {
        d->enable();
        return;
    }
    undoCommandActive = true;
    d->model()->takeItem(d->row, d->parentIndex);
    undoCommandActive = false;
}

bool UndoListCommand::mergeWith(const QUndoCommand *other)
{
    Q_UNUSED(other);
    return false;
}

UndoInsertCommand::UndoInsertCommand(int row, const QModelIndex &parentIndex, QUndoCommand *parent)
    :   UndoListCommand(*(new UndoListCommandPrivate(row, parentIndex)), parent)
{}

UndoRemoveCommand::UndoRemoveCommand(IModelItem *item, int row, const QModelIndex &parentIndex, QUndoCommand *parent)
    :   UndoListCommand(*(new UndoListCommandPrivate(item, row, parentIndex)), parent)
{}

class UndoStackPrivate
{
public:
    UndoStack *q;
    QList<UndoDataCommand*> dataChanges;
    QList<UndoInsertCommand*> inserts;
    QList<UndoRemoveCommand*> removes;

    UndoStackPrivate(UndoStack *q)
        :   q(q)
    {}
};

UndoStack::UndoStack(QObject *parent)
    :   QUndoStack(parent)
    ,   d(new UndoStackPrivate(this))
{
    IDatabase *db = IDatabase::instance();
    connect(db, SIGNAL(databaseAboutToBeRead()), SLOT(databaseAboutToBeRead()));
    connect(db, SIGNAL(databaseRead()), SLOT(databaseRead()));

    Model *model = interfaceToObject_cast<Model>(db->model());
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
    if (Mi::ListItem == topLeft.data(Mi::ItemTypeRole))
        return;
    d->dataChanges.append(new UndoDataCommand(IDatabase::instance()->model()->itemFromIndex(topLeft)));
}

void UndoStack::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);
    if (undoCommandActive || databaseReading)
        return;
    if (Mi::ListItem == topLeft.data(Mi::ItemTypeRole))
        return;
    IModelItem *item = IDatabase::instance()->model()->itemFromIndex(topLeft);
    const int n = d->dataChanges.count();
    for (int i = 0;  i < n;  ++i) {
        UndoDataCommand *cmd = d->dataChanges.at(i);
        if (item != cmd->item())
            continue;
        cmd->updateNewData();
        d->dataChanges.removeAt(i);
        push(cmd);
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
    d->inserts.append(new UndoInsertCommand(start, parent));
}

void UndoStack::rowsInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(end);
    if (undoCommandActive || databaseReading)
        return;
    const int n = d->inserts.count();
    for (int i = 0;  i < n;  ++i) {
        UndoInsertCommand *cmd = d->inserts.at(i);
        if (parent != cmd->parentIndex() || start != cmd->row())
            continue;
        d->inserts.removeAt(i);
        push(cmd);
        IModel *model = IDatabase::instance()->model();
        cmd->setItem(model->itemFromIndex(model->index(start, parent)));
        break;
    }
}

void UndoStack::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(end);
    if (undoCommandActive || databaseReading)
        return;
    IModel *model = IDatabase::instance()->model();
    d->removes.append(new UndoRemoveCommand(model->itemFromIndex(model->index(start, parent)), start, parent));
}

void UndoStack::rowsRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(end);
    if (undoCommandActive || databaseReading)
        return;
    const int n = d->removes.count();
    for (int i = 0;  i < n;  ++i) {
        UndoRemoveCommand *cmd = d->removes.at(i);
        if (parent != cmd->parentIndex() || start != cmd->row())
            continue;
        d->removes.removeAt(i);
        push(cmd);
        break;
    }
}
