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

static QObject *orphanage()
{
    static QObject *orphanage = new QObject(IModel::instance());
    return orphanage;
}

static IModel *instance = 0;

IModel::IModel()
{
    ::instance = this;
    connect(this, SIGNAL(modelReset()), SLOT(deleteOrphans()));
}

IModel *IModel::instance()
{
    return ::instance;
}

QModelIndex IModel::index(int row, int column, const QModelIndex &parent) const
{
    IModelItem *parentItem = parent.isValid() ? itemFromIndex(parent) : rootItem();
    if (!parentItem
            || row < 0
            || column < 0
            || parentItem->modelItemCount() <= row
            || 1 <= column)
        return QModelIndex();
    return createIndex(row, column, parentItem);
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
    IModelItem *parentItem = parent.isValid() ? itemFromIndex(parent) : rootItem();
    return parentItem ? parentItem->modelItemCount() : 0;
}

QVariant IModel::data(const QModelIndex &index, int role) const
{
    IModelItem *item = index.isValid() ? itemFromIndex(index) : rootItem();
    return item ? item->data(role) : QVariant();
}

bool IModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    IModelItem *item = index.isValid() ? itemFromIndex(index) : rootItem();
    return item ? item->setData(value, role) : false;
}

Qt::ItemFlags IModel::flags(const QModelIndex &index) const
{
    IModelItem *item = index.isValid() ? itemFromIndex(index) : rootItem();
    return item ? item->flags() : Qt::NoItemFlags;
}

IModelItem *IModel::itemFromIndex(const QModelIndex &index) const
{
    if ((index.row() < 0)
            || (index.column() < 0)
            || (index.model() != this))
        return rootItem();
    IModelItem *parentItem = static_cast<IModelItem*>(index.internalPointer());
    if (!parentItem)
        return rootItem();
    return parentItem->modelItemAt(index.row());
}

QModelIndex IModel::indexFromItem(const IModelItem *item) const
{
    if (!item)
        return QModelIndex();
    IModelItem *parentItem = item->parentModelItem();
    if (!parentItem)
        return QModelIndex();
    return createIndex(parentItem->modelItemIndex(item), 0, parentItem);
}

bool IModel::insertItem(IModelItem *item, int row, const QModelIndex &parent)
{
    if (Mi::ListItem != parent.data(Mi::ItemTypeRole))
        return false;
    ObjectList *list = interfaceToObject_cast<ObjectList>(itemFromIndex(parent));
    if (!list)
        return false;
    list->insert(row, interfaceToObject_cast<Object>(item));
    return true;
}

void IModel::removeItem(int row, const QModelIndex &parent)
{
    if (Mi::ListItem != parent.data(Mi::ItemTypeRole))
        return;
    ObjectList *list = interfaceToObject_cast<ObjectList>(itemFromIndex(parent));
    if (!list)
        return;
    QObject *object = list->objectAt(row);
    list->removeAt(row);
    object->setParent(orphanage());
}

IModelItem *IModel::takeItem(int row, const QModelIndex &parent)
{
    if (Mi::ListItem != parent.data(Mi::ItemTypeRole))
        return 0;
    ObjectList *list = interfaceToObject_cast<ObjectList>(itemFromIndex(parent));
    if (!list)
        return 0;
    IModelItem *item = list->modelItemAt(row);
    QObject *object = list->objectAt(row);
    list->removeAt(row);
    object->setParent(orphanage());
    return item;
}

void IModel::deleteOrphans()
{
    foreach (QObject *child, orphanage()->children())
        delete child;
}
