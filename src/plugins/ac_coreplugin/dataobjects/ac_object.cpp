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
        Object *child = object_cast<Object>(qchild);
        if (child)
            child->d_ptr->setModel(model);
    }
}

QModelIndex ObjectPrivate::modelIndex() const
{
    return model ? model->d->indexFromItem(q_ptr) : QModelIndex();
}

void ObjectPrivate::beginChangeData()
{
    if (model) {
        QModelIndex index = modelIndex();
        emit model->dataAboutToBeChanged(index, index);
    }
}

void ObjectPrivate::endChangeData()
{
    if (model) {
        QModelIndex index = modelIndex();
        emit model->dataChanged(index, index);
    }
}

void ObjectPrivate::beginInsertObjects(int first, int last)
{
    if (model) {
        QModelIndex index = modelIndex();
        model->beginInsertRows(index, first, last);
        emit model->dataAboutToBeChanged(index, index);
    }
}

void ObjectPrivate::endInsertObjects()
{
    if (model) {
        QModelIndex index = modelIndex();
        model->endInsertRows();
        emit model->dataChanged(index, index);
    }
}

void ObjectPrivate::beginRemoveObjects(int first, int last)
{
    if (model) {
        QModelIndex index = modelIndex();
        model->beginRemoveRows(index, first, last);
        emit model->dataAboutToBeChanged(index, index);
    }
}

void ObjectPrivate::endRemoveObjects()
{
    if (model) {
        QModelIndex index = modelIndex();
        model->endRemoveRows();
        emit model->dataChanged(index, index);
    }
}

void Object::setParent(Object *parent)
{
    if (parent == QObject::parent())
        return;
    QObject *oldParent = QObject::parent();
    ObjectList *oldList = object_cast<ObjectList>(oldParent);
    if (oldList)
        oldList->remove(this);
    d_ptr->setModel(parent ? parent->d_ptr->model : 0);
    QObject::setParent(parent);
    ObjectList *newList = object_cast<ObjectList>(parent);
    if (newList)
        newList->append(this);
}

QVariant Object::data(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return objectName();
    case Mi::ItemTypeRole:
        return type();
    case Mi::NameRole:
        return name();
    default:
        return QVariant();
    }
}

bool Object::setData(const QVariant &value, int role)
{
    if (Mi::NameRole != role) {
        Q_ASSERT(false);
        return false;
    } else {
        QString name = value.toString();
        if (objectName() != name) {
            d_ptr->beginChangeData();
            setObjectName(name);
            d_ptr->endChangeData();
        }
    }
    return true;
}
