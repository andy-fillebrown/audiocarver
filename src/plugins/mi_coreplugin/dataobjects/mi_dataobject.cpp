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
#include <mi_iorphanage.h>
#include <mi_scopeddatachange.h>
#include <mi_scopedparentchange.h>

Q_IAGGREGATOR_INIT_ROLES(DataObject) =
{
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

bool DataObject::setName(const QString &name)
{
    if (_name == name)
        return false;
    if (!name.isEmpty() && _parent && _parent->isList()) {
        IModelList *list = query<IModelList>(_parent);
        if (list && list->containsObjectNamed(_name))
            return false;
    }
    Q_SCOPED_DATA_CHANGE((Mi::NameRole))
    _name = name;
    return true;
}

void DataObject::setParent(DataObject *parent)
{
    if (_parent == parent)
        return;
    Q_SCOPED_PARENT_CHANGE(())
    if (!parent) {
        IOrphanage *orphanage = IOrphanage::instance();
        if (orphanage)
            orphanage->append(this);
    }
    _parent = parent;
}

void DataObject::dataAboutToBeChanged(const DataObject *dataObject, int role, Mi::NotificationFlags notificationFlags)
{
    if (this == dataObject) {
        if (Mi::NotifyModel & notificationFlags) {
            IModel *model = IModel::instance();
            if (model) {
                const IModelData *model_data = const_query<IModelData>(this);
                if (model_data)
                model->beginChangeData(model_data, role);
            }
        }
    }
}

void DataObject::dataChanged(const DataObject *dataObject, int role, Mi::NotificationFlags notificationFlags)
{
    if (this == dataObject) {
        if (Mi::NotifyModel & notificationFlags) {
            IModel *model = IModel::instance();
            if (model) {
                const IModelData *model_data = const_query<IModelData>(this);
                if (model_data)
                    model->endChangeData(model_data, role);
            }
        }
    }
}

void DataObject::parentAboutToBeChanged(const DataObject *dataObject, Mi::NotificationFlags notificationFlags)
{
    if (this == dataObject) {
        if (Mi::NotifyModel & notificationFlags) {
            IModel *model = IModel::instance();
            if (model) {
                const IModelItem *model_item = const_query<IModelItem>(this);
                if (model_item)
                    model->beginChangeParent(model_item);
            }
        }
    }
}

void DataObject::parentChanged(const DataObject *dataObject, Mi::NotificationFlags notificationFlags)
{
    if (this == dataObject) {
        if (Mi::NotifyModel & notificationFlags) {
            IModel *model = IModel::instance();
            if (model) {
                const IModelItem *model_item = const_query<IModelItem>(this);
                if (model_item)
                    model->endChangeParent(model_item);
            }
        }
    }
}
