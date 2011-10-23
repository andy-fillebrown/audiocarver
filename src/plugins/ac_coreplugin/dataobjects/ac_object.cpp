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

#include "ac_object.h"

#include <ac_model.h>
#include <ac_objectlist.h>

void ObjectPrivate::setModel(Model *model)
{
    if (this->model == model)
        return;
    this->model = model;
    const QObjectList &qchildren = q_ptr->children();
    foreach (QObject *qchild, qchildren) {
        Object *child = qobject_cast<Object*>(qchild);
        if (child)
            child->d_ptr->setModel(model);
    }
}

void ObjectPrivate::beginChangeData()
{
    if (model) {
        QModelIndex index = model->d->indexFromItem(q_ptr);
        emit model->dataAboutToBeChanged(index, index);
    }
}

void ObjectPrivate::endChangeData()
{
    if (model) {
        QModelIndex index = model->d->indexFromItem(q_ptr);
        emit model->dataChanged(index, index);
    }
}

void ObjectPrivate::beginInsertObjects(int first, int last)
{
    if (model)
        model->beginInsertColumns(model->d->indexFromItem(q_ptr), first, last);
}

void ObjectPrivate::endInsertObjects()
{
    if (model)
        model->endInsertColumns();
}

void ObjectPrivate::beginRemoveObjects(int first, int last)
{
    if (model)
        model->beginRemoveColumns(model->d->indexFromItem(q_ptr), first, last);
}

void ObjectPrivate::endRemoveObjects()
{
    if (model)
        model->endRemoveColumns();
}

void Object::setParent(Object *parent)
{
    if (parent == QObject::parent())
        return;
    QObject *oldParent = QObject::parent();
    ObjectList *oldList = qobject_cast<ObjectList*>(oldParent);
    if (oldList)
        oldList->remove(this);
    QObject::setParent(parent);
    ObjectList *newList = qobject_cast<ObjectList*>(parent);
    if (newList)
        newList->append(this);
}

QVariant Object::data(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return objectName();
    case Ac::ItemTypeRole:
        return type();
    default:
        return QVariant();
    }
}
