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

#include "mi_modelitem.h"

#include <mi_dataobject.h>
#include <mi_iobject.h>

ModelItem::ModelItem(DataObject *aggregator)
    :   _aggregator(aggregator)
{}

const IAggregator *ModelItem::aggregator() const
{
    return _aggregator;
}

void ModelItem::setParent(IModelItem *parent)
{
    if (_parent == parent)
        return;
    _parent = parent;

    // Set QObject parent.
    IObject *object_i = query<IObject>(_aggregator);
    if (!object_i)
        return;
    IObject *parent_object_i = query<IObject>(parent, NoAutoCreate);
    if (!parent_object_i)
        return;
    object_i->setParent(parent_object_i);
}

bool ModelItem::setName(const QString &name)
{
    if (_name == name)
        return false;
    _name = name;

    // Set QObject object name.
    IObject *object_i = query<IObject>(_aggregator, NoAutoCreate);
    if (object_i)
        object_i->setObjectName(_name);

    return true;
}

QVariant ModelItem::data(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Mi::NameRole:
        return name();
    default:
        Q_ASSERT(false);
        return QVariant();
    }
}

bool ModelItem::setData(const QVariant &data, int role)
{
    switch (role) {
    case Qt::EditRole:
    case Mi::NameRole:
        return setName(data.toString());
    default:
        Q_ASSERT(false);
        return false;
    }
}
