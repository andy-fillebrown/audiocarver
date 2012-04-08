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

#include "mi_imodel.h"

#include <mi_objectlist.h>

static IModel *instance = 0;

IModel::IModel()
{
    ::instance = this;
    connect(this, SIGNAL(dataChanged(IModelItem*,int)), SLOT(_dataChanged(IModelItem*)));
    connect(this, SIGNAL(itemAboutToBeInserted(IModelItemList*,int)), SLOT(_itemAboutToBeInserted(IModelItemList*,int)));
    connect(this, SIGNAL(itemInserted(IModelItemList*,int)), SLOT(_itemInserted()));
    connect(this, SIGNAL(itemAboutToBeRemoved(IModelItemList*,int)), SLOT(_itemAboutToBeRemoved(IModelItemList*,int)));
    connect(this, SIGNAL(itemRemoved(IModelItemList*,int)), SLOT(_itemRemoved()));
    connect(this, SIGNAL(modelReset()), SLOT(_deleteOrphans()));
}

IModel *IModel::instance()
{
    return ::instance;
}

QObject *IModel::orphanage()
{
    static QObject *orphanage = new QObject(IModel::instance());
    return orphanage;
}

IModelItem *IModel::itemFromIndex(const QModelIndex &index) const
{
    if ((index.row() < 0)
            || (index.column() < 0)
            || (index.model() != this))
        return rootItem();
    IModelItem *parent_item = static_cast<IModelItem*>(index.internalPointer());
    if (!parent_item)
        return rootItem();
    return parent_item->at(index.row());
}

QModelIndex IModel::indexFromItem(const IModelItem *item) const
{
    if (!item)
        return QModelIndex();
    IModelItem *parent_item = item->parent();
    if (!parent_item)
        return QModelIndex();
    return createIndex(parent_item->indexOf(item), 0, parent_item);
}

QModelIndex IModel::index(int row, int column, const QModelIndex &parent) const
{
    IModelItem *parent_item = parent.isValid() ? itemFromIndex(parent) : rootItem();
    if (!parent_item
            || row < 0
            || column < 0
            || parent_item->count() <= row
            || 1 <= column)
        return QModelIndex();
    return createIndex(row, column, parent_item);
}

QModelIndex IModel::parent(const QModelIndex &child) const
{
    if (child.row() < 0
            || child.column() < 0
            || child.model() != this)
        return QModelIndex();
    return indexFromItem(static_cast<IModelItem*>(child.internalPointer()));
}

int IModel::rowCount(const QModelIndex &parent) const
{
    IModelItem *parent_item = parent.isValid() ? itemFromIndex(parent) : rootItem();
    return parent_item ? parent_item->count() : 0;
}

QVariant IModel::data(const QModelIndex &index, int role) const
{
    IModelItem *item = index.isValid() ? itemFromIndex(index) : rootItem();
    return item ? item->data(role) : QVariant();
}

bool IModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (isLocked())
        return false;
    IModelItem *item = index.isValid() ? itemFromIndex(index) : rootItem();
    return item ? item->setData(value, role) : false;
}

Qt::ItemFlags IModel::flags(const QModelIndex &index) const
{
    IModelItem *item = index.isValid() ? itemFromIndex(index) : rootItem();
    return item ? item->flags() : Qt::NoItemFlags;
}

void IModel::_dataChanged(IModelItem *item)
{
    QModelIndex index = indexFromItem(item);
    emit QAbstractItemModel::dataChanged(index, index);
}

void IModel::_itemAboutToBeInserted(IModelItemList *list, int i)
{
    beginInsertRows(indexFromItem(list), i, i);
}

void IModel::_itemInserted()
{
    endInsertRows();
}

void IModel::_itemAboutToBeRemoved(IModelItemList *list, int i)
{
    beginRemoveRows(indexFromItem(list), i, i);
}

void IModel::_itemRemoved()
{
    endRemoveRows();
}

void IModel::_deleteOrphans()
{
    foreach (QObject *child, orphanage()->children())
        delete child;
}
