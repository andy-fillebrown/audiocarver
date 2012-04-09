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

#include "mi_dataobject.h"

#include <mi_imodel.h>
#include <mi_imodellist.h>
#include <mi_scopedchange.h>

DataObject::~DataObject()
{}

void DataObject::setParent(DataObject *parent)
{
    if (_parent == parent)
        return;
    if (!parent)
        IModel::instance()->orphan(query<IModelItem>(this));
}

bool DataObject::setName(const QString &name)
{
    if (_name == name)
        return false;
    if (!name.isEmpty()) {
        IModelList *list = query<IModelList>(_parent);
        if (list && list->has(_name))
            return false;
    }
    Q_MI_SCOPED_CHANGE(Mi::NameRole);
    _name = name;
    return true;
}

QVariant DataObject::ModelData::get(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Mi::NameRole:
        return dataObject()->name();
    default:
        Q_ASSERT(false);
        return QVariant();
    }
}

bool DataObject::ModelData::set(const QVariant &data, int role)
{
    switch (role) {
    case Qt::EditRole:
    case Mi::NameRole:
        return dataObject()->setName(data.toString());
    default:
        Q_ASSERT(false);
        return false;
    }
}
