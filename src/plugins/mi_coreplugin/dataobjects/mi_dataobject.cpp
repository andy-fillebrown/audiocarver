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

Q_I_INIT__AGGREGATOR__ROLES(DataObject) {
Mi::NameRole
};

IAggregator *DataObject::init()
{
    return this;
}

IAggregate *DataObject::ModelData::init()
{
    _item = query<IModelItem>(a());
    return this;
}

IAggregate *DataObject::ModelItem::init()
{
    return this;
}

void DataObject::ModelData::dataAboutToBeChanged(const IModelData *data, int role, Mi::NotificationFlags notificationFlags)
{
    if (Mi::NotifyModel & notificationFlags) {
        IModel *model = IModel::instance();
        if (model)
            model->beginChange(data, role);
    }
}

void DataObject::ModelData::dataChanged(const IModelData *data, int role, Mi::NotificationFlags notificationFlags)
{
    if (Mi::NotifyModel & notificationFlags) {
        IModel *model = IModel::instance();
        if (model)
            model->endChange(data, role);
    }
}
