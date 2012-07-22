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

#include "ac_undo.h"

#include <mi_idatabase.h>
#include <mi_ieditor.h>
#include <mi_imodel.h>
#include <mi_imodeldata.h>
#include <mi_imodellist.h>

#include <ac_gui_viewmanager.h>

#include <ac_gui_namespace.h>

#include <mi_core_qmodel.h>

#include <QModelIndex>

static bool undoCommandActive = false;

class UndoCommandPrivate
{
    uint enabled : 1;

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
        return query<IModel>(IDatabase::instance());
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
        QMap<int, QVariant> values;
        IModelData *data = query<IModelData>(item);
        const int n = data->roleCount();
        for (int i = 0;  i < n;  ++i) {
            const int role = data->roleAt(i);
            const QVariant value = data->getVariant(role);
            values.insert(role, value);
        }
        return values;
    }

    void setData(const QMap<int, QVariant> &values)
    {
        IModelData *data = query<IModelData>(item);
        const QList<int> keys = values.keys();
        const int n = keys.count();
        for (int i = 0;  i < n;  ++i) {
            const int &role = keys.at(i);
            data->set(values.value(role), role);
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
    IModelList *list;

    UndoListCommandPrivate(int row, IModelList *list)
        :   row(row)
        ,   list(list)
    {}

    UndoListCommandPrivate(IModelItem *item, int row, IModelList *list)
        :   UndoModelItemCommandPrivate(item)
        ,   row(row)
        ,   list(list)
    {}

    ~UndoListCommandPrivate()
    {}
};

UndoListCommand::UndoListCommand(UndoListCommandPrivate &dd, QUndoCommand *parent)
    :   UndoModelItemCommand(dd, parent)
{}

IModelList *UndoListCommand::list() const
{
    Q_D(const UndoListCommand);
    return d->list;
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
    list()->insert(d->row, item());
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
    list()->removeAt(row());
    undoCommandActive = false;
}

bool UndoListCommand::mergeWith(const QUndoCommand *other)
{
    Q_UNUSED(other);
    return false;
}

UndoInsertCommand::UndoInsertCommand(int row, IModelList *list, QUndoCommand *parent)
    :   UndoListCommand(*(new UndoListCommandPrivate(row, list)), parent)
{}

UndoRemoveCommand::UndoRemoveCommand(IModelItem *item, int row, IModelList *list, QUndoCommand *parent)
    :   UndoListCommand(*(new UndoListCommandPrivate(item, row, list)), parent)
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
//    IQModel *model = query<IQModel>(IDatabase::instance());
//    connect(model, SIGNAL(dataAboutToBeChanged(QModelIndex,QModelIndex)), SLOT(dataAboutToBeChanged(QModelIndex,QModelIndex)));
//    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
//    connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
//    connect(model, SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)), SLOT(rowsAboutToBeInserted(QModelIndex,int,int)));
//    connect(model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(rowsInserted(QModelIndex,int,int)));
//    connect(model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)), SLOT(rowsAboutToBeRemoved(QModelIndex,int,int)));
//    connect(model, SIGNAL(rowsRemoved(QModelIndex,int,int)), SLOT(rowsRemoved(QModelIndex,int,int)));
}

UndoStack::~UndoStack()
{
    delete d;
}

void UndoStack::dataAboutToBeChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);
    if (undoCommandActive
            || IDatabase::instance()->isReading()
            || IEditor::instance()->isCreating())
        return;
    if (Mi::ListItem == topLeft.data(Mi::ItemTypeRole))
        return;
//    d->dataChanges.append(new UndoDataCommand(query<IModel>(IDatabase::instance())->itemFromIndex(topLeft)));
}

void UndoStack::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
//    if (undoCommandActive
//            || IDatabase::instance()->isReading()
//            || IEditor::instance()->isCreating())
//        return;
//    if (Mi::ListItem == topLeft.data(Mi::ItemTypeRole))
//        return;
//    IModelItem *item = query<IModel>(IDatabase::instance())->itemFromIndex(topLeft);
//    const int n = d->dataChanges.count();
//    for (int i = 0;  i < n;  ++i) {
//        UndoDataCommand *cmd = d->dataChanges.at(i);
//        if (item != cmd->item())
//            continue;
//        cmd->updateNewData();
//        d->dataChanges.removeAt(i);
//        push(cmd);
//        break;
//    }
}

void UndoStack::modelReset()
{
    clear();
}

void UndoStack::rowsAboutToBeInserted(const QModelIndex &parent, int start, int end)
{
//    if (undoCommandActive || IDatabase::instance()->isReading())
//        return;
//    d->inserts.append(new UndoInsertCommand(start, query<IModelList>(query<IModel>(IDatabase::instance())->itemFromIndex(parent))));
}

void UndoStack::rowsInserted(const QModelIndex &parent, int start, int end)
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

void UndoStack::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
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

void UndoStack::rowsRemoved(const QModelIndex &parent, int start, int end)
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
