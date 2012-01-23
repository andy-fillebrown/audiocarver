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

#include <mi_itemselectionmodel.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

class PropertyModelPrivate
{
public:
    PropertyModel *q;
    QList<const ItemSelectionModel*> selectionModels;
    QList<const IModelItem*> selectedItems;
    QMap<int, QVariant> dataMap;

    PropertyModelPrivate(PropertyModel *q)
        :   q(q)
    {}

    void update()
    {
        selectedItems.clear();
        foreach (const ItemSelectionModel *selection_model, selectionModels) {
            QList<IModelItem*> selected_items = selection_model->selectedItems();
            foreach (const IModelItem *selected_item, selected_items) {
                if (selectedItems.contains(selected_item))
                    continue;
                selectedItems.append(selected_item);
            }
        }

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
    if (!connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged()), Qt::UniqueConnection))
        return;

    d->selectionModels.append(selectionModel);
    d->update();
}

void PropertyModel::removeSelectionModel(ItemSelectionModel *selectionModel)
{
    if (!d->selectionModels.contains(selectionModel))
        return;

    selectionModel->disconnect(this);
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

QVariant PropertyModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);

    if (Qt::DisplayRole != role)
        return QVariant();

    const int column = index.column();
    const int row = index.row();

    QVariant value;
    if (0 == column) {
        QList<int> keys = d->dataMap.keys();
        if (row < keys.count())
            value = keys.at(row);
    } else if (1 == column) {
        QList<QVariant> values = d->dataMap.values();
        if (row < values.count())
            value = values.at(row);
    }
    return value;
}

bool PropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index);
    Q_UNUSED(value);
    Q_UNUSED(role);
    return false;
}

void PropertyModel::selectionChanged()
{
    d->update();
}
