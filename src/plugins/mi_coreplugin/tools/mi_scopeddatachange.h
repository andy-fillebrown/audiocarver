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

#ifndef MI_SCOPEDDATACHANGE_H
#define MI_SCOPEDDATACHANGE_H

#include <mi_database_object.h>

#include <mi_imodel.h>
#include <mi_imodeldata.h>
#include <mi_imodeldatawatcher.h>

namespace Database {

class ScopedDataChange
{
    const IModelData *_data;
    const QList<IModelDataWatcher*> &_watchers;
    const int _role;
    const Mi::NotificationFlags _notificationFlags;

public:
    ScopedDataChange(Object *object, int role, Mi::NotificationFlags notificationFlags = Mi::NotifyModel)
        :   _data(const_query<IModelData>(object))
        ,   _watchers(object->dataWatchers())
        ,   _role(role)
        ,   _notificationFlags(notificationFlags)
    {
        if (!_data)
            return;
        foreach (IModelDataWatcher *watcher, _watchers)
            watcher->dataAboutToBeChanged(_data, _role);
        if (Mi::NotifyModel & _notificationFlags) {
            IModel *model = IModel::instance();
            if (model)
                model->beginChangeData(_data, _role);
        }
    }

    ~ScopedDataChange()
    {
        if (!_data)
            return;
        foreach (IModelDataWatcher *watcher, _watchers)
            watcher->dataChanged(_data, _role);
        if (Mi::NotifyModel & _notificationFlags) {
            IModel *model = IModel::instance();
            if (model)
                model->endChangeData(_data, _role);
        }
    }
};

} // namespace Database

#endif // MI_SCOPEDDATACHANGE_H
