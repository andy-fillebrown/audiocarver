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

#ifndef MI_CORE_SCOPEDDATACHANGE_H
#define MI_CORE_SCOPEDDATACHANGE_H

#include "mi_iaggregate.h"
#include "mi_imodeldata.h"
#include "mi_imodeldatawatcher.h"

namespace Mi {
namespace Core {

class ScopedDataChange
{
    IModelData *_data;
    const int _role;
    const DataChangeType _dataChangeType;
    QList<IModelDataWatcher*> _watchers;

public:
    ScopedDataChange(const IAggregate *aggregate, int role, DataChangeType dataChangeType = PermanentDataChange)
        :   _data(query<IModelData>(aggregate))
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

} // namespace Core
} // namespace Mi

#endif // MI_CORE_SCOPEDDATACHANGE_H
