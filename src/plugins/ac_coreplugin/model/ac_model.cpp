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

#include "ac_model.h"
#include <ac_item.h>

Model::Model(QObject *parent)
    :   AbstractItemModel(parent)
    ,   _score(new Score)
    ,   _layoutAboutToBeChangedEmitted(false)
{
    _score->setModel(this);
}

Model::~Model()
{
    delete _score;
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    Item *parentItem = parent.isValid() ? itemFromIndex(parent) : _score;
    if (!parentItem
            || row < 0
            || column < 0
            || parentItem->childCount() <= row
            || 1 <= column)
        return QModelIndex();
    return createIndex(row, column, parentItem);
}

QModelIndex Model::parent(const QModelIndex &child) const
{
    if (child.row() < 0 || child.column() < 0 || child.model() != this)
        return QModelIndex();
    return indexFromItem(static_cast<Item*>(child.internalPointer()));
}

int Model::rowCount(const QModelIndex &parent) const
{
    Item *parentItem = parent.isValid() ? itemFromIndex(parent) : _score;
    return parentItem ? parentItem->childCount() : 0;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    Item *itm = index.isValid() ? itemFromIndex(index) : _score;
    return itm ? itm->data(role) : QVariant();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Item *itm = index.isValid() ? itemFromIndex(index) : _score;
    return itm ? itm->setData(value, role) : false;
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    Item *itm = index.isValid() ? itemFromIndex(index) : _score;
    return itm ? itm->flags() : Qt::NoItemFlags;
}

QModelIndex Model::indexFromItem(Item *item) const
{
    if (!item)
        return QModelIndex();
    Item *parentItem = item->parent();
    if (!parentItem)
        return QModelIndex();
    return createIndex(parentItem->childIndex(item), 0, parentItem);
}

Item *Model::itemFromIndex(const QModelIndex &index) const
{
    if ((index.row() < 0) || (index.column() < 0) || (index.model() != this))
        return 0;
    Item *parentItem = static_cast<Item*>(index.internalPointer());
    if (!parentItem)
        return 0;
    return parentItem->childAt(index.row());
}
