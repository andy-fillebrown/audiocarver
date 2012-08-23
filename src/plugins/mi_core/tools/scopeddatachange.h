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

#ifndef SCOPEDDATACHANGE_H
#define SCOPEDDATACHANGE_H

#include "mi_core_namespace.h"
#include <iaggregate.h>
#include <imodeldata.h>
#include <imodeldatawatcher.h>

class ScopedDataChange
{
    const IModelData *_data;
    const int _role;
    const int _dataChangeType;
    QList<IModelDataWatcher*> _watchers;

public:
    ScopedDataChange(const IModelData *data, int role, int dataChangeType = Mi::PermanentDataChange)
        :   _data(data)
        ,   _role(role)
        ,   _dataChangeType(dataChangeType)
    {
        if (!_data)
            return;
        const QList<IUnknown*> &components = query<IAggregate>(_data)->components();
        foreach (IUnknown *component, components)
            if (component->isTypeOfInterface(I::IModelDataWatcher))
                _watchers.append(query<IModelDataWatcher>(component));
        foreach (IModelDataWatcher *watcher, _watchers)
            watcher->beginChangeData(_data, _role, _dataChangeType);
    }

    ~ScopedDataChange()
    {
        if (!_data)
            return;
        foreach (IModelDataWatcher *watcher, _watchers)
            watcher->beginChangeData(_data, _role, _dataChangeType);
    }
};

#endif
