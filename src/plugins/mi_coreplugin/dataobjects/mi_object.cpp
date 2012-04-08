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

#include "mi_object.h"

#include <mi_imodel.h>

#include <QModelIndex>

QVariant ObjectPrivate::ModelItemHelper::data(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Mi::NameRole:
        return query<IModelItem>(q_ptr)->name();
    case Mi::ItemTypeRole:
        return query<IModelItem>(q_ptr)->type();
    default:
        return QVariant();
    }
}

bool ObjectPrivate::ModelItemHelper::setData(const QVariant &data, int role)
{
    if (Mi::NameRole == role) {
        query<IModelItem>(q_ptr)->setName(data.toString());
        return true;
    }
    return false;
}

void ObjectPrivate::setParent(QObject *parent)
{
    if (parent == q_ptr->parent())
        return;
    q_ptr->setParent(parent);
    Object *new_parent = object_cast<Object>(parent);
    setModel(new_parent ? new_parent->d_ptr->model : 0);
}

void ObjectPrivate::clearParent()
{
    setParent(IModel::orphanage());
}

void ObjectPrivate::setModel(IModel *model)
{
    if (this->model == model)
        return;
    this->model = model;
    const QObjectList &children = q_ptr->children();
    foreach (QObject *child, children) {
        Object *object = object_cast<Object>(child);
        if (object)
            object->d_ptr->setModel(model);
    }
}

void ObjectPrivate::beginChangeData(int role)
{
    if (model)
        emit model->dataAboutToBeChanged(modelItem(), role);
}

void ObjectPrivate::endChangeData(int role)
{
    if (model)
        emit model->dataChanged(modelItem(), role);
}
