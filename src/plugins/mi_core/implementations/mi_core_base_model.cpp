/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "mi_core_base_model.h"
#include <iaggregate.h>
#include <idatabase.h>
#include <imodel.h>
#include <imodelitem.h>
#include <isession.h>

using namespace Qt;

static IModel *instance = 0;

IModel *IModel::instance()
{
    return ::instance;
}

namespace Base {

void *Model::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : ISession::instance()->queryInterface(interfaceType);
}

Model::Model()
{
    IAggregate *aggregate = ISession::instance();
    aggregate->removeComponent(::instance);
    delete ::instance;
    ::instance = this;
    aggregate->appendComponent(this);
}

Model::~Model()
{
    ::instance = 0;
}

void Model::beginChangeData(IModelItem *item, int role)
{
    emit dataAboutToBeChanged(item, role);
}

void Model::endChangeData(IModelItem *item, int role)
{
    emit dataChanged(item, role);
    emit dataChanged(indexFromItem(item));
}

void Model::beginInsertItem(IModelItem *list, int index)
{
    emit itemAboutToBeInserted(list, index);
    beginInsertRows(indexFromItem(list), index, index);
}

void Model::endInsertItem(IModelItem *list, int index)
{
    emit itemInserted(list, index);
    endInsertRows();
}

void Model::beginRemoveItem(IModelItem *list, int index)
{
    emit itemAboutToBeRemoved(list, index);
    beginRemoveRows(indexFromItem(list), index, index);
}

void Model::endRemoveItem(IModelItem *list, int index)
{
    emit itemRemoved(list, index);
    endRemoveRows();
}

IModelItem *Model::itemFromIndex(const QModelIndex &index) const
{
    if ((index.row() < 0)
            || (index.column() < 0)
            || (index.model() != this))
        return IDatabase::instance()->rootItem();
    IModelItem *parent_item = static_cast<IModelItem*>(index.internalPointer());
    return parent_item ? parent_item->itemAt(index.row()) : IDatabase::instance()->rootItem();
}

QModelIndex Model::indexFromItem(IModelItem *item) const
{
    if (!item)
        return QModelIndex();
    IModelItem *parent = item->parent();
    if (!parent)
        return QModelIndex();
    QModelIndex index = createIndex(parent->indexOfItem(item), 0, parent);
    Q_ASSERT(index.isValid());
    return index;
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    IModelItem *parent_item = parent.isValid() ? itemFromIndex(parent) : IDatabase::instance()->rootItem();
    if (!parent_item
            || row < 0
            || column < 0
            || parent_item->itemCount() <= row
            || 1 <= column)
        return QModelIndex();
    QModelIndex index = createIndex(row, column, parent_item);
    Q_ASSERT(index.isValid());
    return index;
}

QModelIndex Model::parent(const QModelIndex &child) const
{
    if (child.row() < 0
            || child.column() < 0
            || child.model() != this)
        return QModelIndex();
    return indexFromItem(static_cast<IModelItem*>(child.internalPointer()));
}

int Model::rowCount(const QModelIndex &parent) const
{
    IModelItem *parent_item = itemFromIndex(parent);
    return parent_item ? parent_item->itemCount() : 0;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    IModelItem *item = itemFromIndex(index);
    return item ? item->getValue(role) : QVariant();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    IModelItem *item = itemFromIndex(index);
    return item ? item->setValue(role, value) : false;
}

ItemFlags Model::flags(const QModelIndex &index) const
{
    IModelItem *item = itemFromIndex(index);
    return item ? ItemFlags(item->flags()) : NoItemFlags;
}

}
