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

#include "acobject.h"

#include <acmodel.h>

void ObjectPrivate::setModel(Model *model)
{
    if (this->model == model)
        return;
    this->model = model;
    const QObjectList &qchildren = q->children();
    foreach (QObject *qchild, qchildren) {
        Object *child = qobject_cast<Object*>(qchild);
        if (child)
            child->d_ptr->setModel(model);
    }
}

void ObjectPrivate::beginInsertObjects(int first, int last)
{
    if (model)
        model->beginInsertColumns(model->indexFromItem(q), first, last);
}

void ObjectPrivate::endInsertObjects()
{
    if (model)
        model->endInsertColumns();
}

void ObjectPrivate::beginRemoveObjects(int first, int last)
{
    if (model)
        model->beginRemoveColumns(model->indexFromItem(q), first, last);
}

void ObjectPrivate::endRemoveObjects()
{
    if (model)
        model->endRemoveColumns();
}

QVariant Object::data(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return objectName();
    case ItemTypeRole:
        return type();
    default:
        return QVariant();
    }
}
