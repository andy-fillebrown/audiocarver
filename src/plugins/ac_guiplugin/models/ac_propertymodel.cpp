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

#include "ac_propertymodel.h"

#include <ac_namespace.h>

#include <mi_ieditor.h>
#include <mi_itemselectionmodel.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <QTimer>

class PropertyModelPrivate
{
public:
    PropertyModel *q;
    QList<const QAbstractItemModel*> models;
    QList<const ItemSelectionModel*> selectionModels;
    QList<IModelItem*> selectedItems;
    QMap<int, QVariant> dataMap;
    QTimer *updateTimer;

    PropertyModelPrivate(PropertyModel *q)
        :   q(q)
        ,   updateTimer(new QTimer(q))
    {
        updateTimer->setSingleShot(true);
    }

    void update()
    {
        QList<const QAbstractItemModel*> current_models;
        foreach (const ItemSelectionModel *selection_model, selectionModels)
            current_models.append(selection_model->model());
        foreach (const QAbstractItemModel *model, current_models)
            if (!models.contains(model))
                updateTimer->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SIGNAL(timeout()));
        foreach (const QAbstractItemModel *model, models)
            if (!current_models.contains(model))
                QObject::disconnect(model, "", updateTimer, "");
        models = current_models;

        selectedItems.clear();
        foreach (const ItemSelectionModel *selection_model, selectionModels) {
            QList<IModelItem*> selected_items = selection_model->selectedItems();
            foreach (IModelItem *selected_item, selected_items) {
                if (selectedItems.contains(selected_item))
                    continue;
                selectedItems.append(selected_item);
            }
        }

        if (selectedItems.isEmpty())
            selectedItems.append(IModel::instance()->rootItem());

        dataMap.clear();
        foreach (const IModelItem *selected_item, selectedItems) {
            const int role_count = selected_item->persistentRoleCount();
            for (int i = 0;  i < role_count;  ++i) {
                const int role = selected_item->persistentRoleAt(i);
                const QVariant data = selected_item->data(role);
                if (!dataMap.contains(role))
                    dataMap.insert(role, data);
                else if (data != dataMap.value(role)) {
                    dataMap.remove(role);
                    dataMap.insert(role, "<varies>");
                }
            }
        }

        q->reset();
    }
};

static PropertyModel *instance = 0;

PropertyModel::PropertyModel(QObject *parent)
    :   QAbstractTableModel(parent)
    ,   d(new PropertyModelPrivate(this))
{
    connect(d->updateTimer, SIGNAL(timeout()), SLOT(update()));
    ::instance = this;
}

PropertyModel::~PropertyModel()
{
    delete d;
}

PropertyModel *PropertyModel::instance()
{
    return ::instance;
}

void PropertyModel::appendSelectionModel(ItemSelectionModel *selectionModel)
{
    if (!d->updateTimer->connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SIGNAL(timeout()), Qt::UniqueConnection))
        return;
    d->selectionModels.append(selectionModel);
    d->update();
}

void PropertyModel::removeSelectionModel(ItemSelectionModel *selectionModel)
{
    if (!d->selectionModels.contains(selectionModel))
        return;
    selectionModel->disconnect(d->updateTimer);
    d->selectionModels.removeOne(selectionModel);
    d->update();
}

int PropertyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

int PropertyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->dataMap.count();
}

Qt::ItemFlags PropertyModel::flags(const QModelIndex &index) const
{
    const Qt::ItemFlags default_flags = Qt::ItemIsEnabled;
    if (1 == index.column())
        return default_flags | Qt::ItemIsEditable;
    return default_flags;
}

QVariant PropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole != role
            || Qt::Horizontal != orientation
            || section < 0 || 1 < section)
        return QVariant();

    if (0 == section)
        return "Property";
    return "Value";
}

QVariant PropertyModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);

    if (Mi::RoleTypeRole == role)
        return d->dataMap.keys().at(index.row());

    if (Qt::DisplayRole != role
            && Qt::EditRole != role)
        return QVariant();

    const int column = index.column();
    const int row = index.row();

    if (0 == row)
        return QVariant();

    QVariant value;
    if (0 == column) {
        const QList<int> keys = d->dataMap.keys();
        if (row < keys.count())
            value = Ac::itemDataRoleString(keys.at(row));
    } else if (1 == column) {
        const QList<QVariant> values = d->dataMap.values();
        if (row < values.count())
            value = values.at(row);
    }
    return value;
}

bool PropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ((Qt::DisplayRole != role && Qt::EditRole != role)
            ||  1 != index.column())
        return false;

    IEditor *editor = IEditor::instance();
    editor->beginCommand();

    int property_role = d->dataMap.keys().at(index.row());
    foreach (IModelItem *item, d->selectedItems)
        item->setData(value, property_role);

    editor->endCommand();
    return true;
}

void PropertyModel::update()
{
    d->update();
}
