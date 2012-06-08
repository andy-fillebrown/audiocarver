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

#include "mi_database_object.h"

#include <mi_database_objectlist.h>
#include <mi_imodel.h>
#include <mi_iorphanage.h>
#include <mi_scopeddatachange.h>
#include <mi_scopedparentchange.h>

namespace Database {

IAggregator *Object::init()
{
    return this;
}

IAggregate *Object::ModelData::init()
{
    _item = query<IModelItem>(a());
    return this;
}

IAggregate *Object::ModelItem::init()
{
    return this;
}

bool Object::setName(const QString &name)
{
    if (_name == name)
        return false;
    if (!name.isEmpty() && _parent && _parent->isList()) {
        IModelList *list = query<IModelList>(_parent);
        if (list && list->containsObjectNamed(_name))
            return false;
    }
    ScopedDataChange data_change(this, Mi::NameRole);
    _name = name;
    return true;
}

void Object::setParent(Object *parent)
{
    if (_parent == parent)
        return;
    ScopedParentChange parent_change(this);
    IOrphanage *orphanage = IOrphanage::instance();
    if (orphanage) {
        if (!_parent)
            orphanage->remove(this);
        if (!parent)
            orphanage->append(this);
    }
    _parent = parent;
}

ObjectList *Object::list() const
{
    if (_parent->isList())
        return dynamic_cast<ObjectList*>(_parent);
    return 0;
}

void Object::dataAboutToBeChanged(const Object *object, int role, Mi::NotificationFlags notificationFlags)
{
    if (this == object) {
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

void Object::dataChanged(const Object *object, int role, Mi::NotificationFlags notificationFlags)
{
    if (this == object) {
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

void Object::parentAboutToBeChanged(const Object *object, Mi::NotificationFlags notificationFlags)
{
    if (this == object) {
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

void Object::parentChanged(const Object *object, Mi::NotificationFlags notificationFlags)
{
    if (this == object) {
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

} // namespace Database
