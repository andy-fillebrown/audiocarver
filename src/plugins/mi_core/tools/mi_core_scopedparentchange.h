/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef MI_CORE_SCOPEDPARENTCHANGE_H
#define MI_CORE_SCOPEDPARENTCHANGE_H

#include "mi_core_namespace.h"
#include <iaggregate.h>
#include <imodelitem.h>
#include <imodelitemwatcher.h>
#include <QList>

class ScopedParentChange
{
    IModelItem *_item;
    QList<IModelItemWatcher*> _watchers;

public:
    ScopedParentChange(IModelItem *item)
        :   _item(item)
    {
        if (!_item)
            return;
        const QList<IComponent*> &components = query<IAggregate>(_item)->components();
        foreach (IComponent *component, components)
            if (component->isTypeOfInterface(I::IModelItemWatcher))
                _watchers.append(query<IModelItemWatcher>(component));
        foreach (IModelItemWatcher *watcher, _watchers)
            watcher->beginChangeParent(_item);
    }

    ~ScopedParentChange()
    {
        if (!_item)
            return;
        foreach (IModelItemWatcher *watcher, _watchers)
            watcher->endChangeParent(_item);
    }
};

#endif
