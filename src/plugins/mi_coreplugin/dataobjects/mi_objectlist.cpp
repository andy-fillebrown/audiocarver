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

#include <mi_objectlist.h>

#include <mi_imodel.h>

#include <QVariant>

void *ObjectList::queryInterface(int interface) const
{
    Q_D(const ObjectList);
    switch (interface) {
    case Mi::ModelItemListInterface:
        return d->modelItemList();
    default:
        return Object::queryInterface(interface);
    }
}

ScopedItemInsertion::ScopedItemInsertion(ObjectListPrivate *d, int i)
    :   d(d)
    ,   i(i)
{
    d->beginInsertItem(i);
}

ScopedItemInsertion::~ScopedItemInsertion()
{
    d->endInsertItem(i);
}

ScopedItemRemoval::ScopedItemRemoval(ObjectListPrivate *d, int i)
    :   d(d)
    ,   i(i)
{
    d->beginRemoveItem(i);
}

ScopedItemRemoval::~ScopedItemRemoval()
{
    d->endRemoveItem(i);
}

QVariant ObjectListPrivate::ModelItemList::data(int role) const
{
    if (Mi::ListTypeRole == role) {
        Q_I_D(const ObjectList);
        return d->listType;
    }
    return helper.data(role);
}

void ObjectListPrivate::beginInsertItem(int i)
{
    if (model)
        emit model->itemAboutToBeInserted(modelItemList(), i);
}

void ObjectListPrivate::endInsertItem(int i)
{
    if (model)
        emit model->itemInserted(modelItemList(), i);
}

void ObjectListPrivate::beginRemoveItem(int i)
{
    if (model)
        emit model->itemAboutToBeRemoved(modelItemList(), i);
}

void ObjectListPrivate::endRemoveItem(int i)
{
    if (model)
        emit model->itemRemoved(modelItemList(), i);
}
