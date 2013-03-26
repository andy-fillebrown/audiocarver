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

#ifndef MI_CORE_SCOPEDITEMREMOVE_H
#define MI_CORE_SCOPEDITEMREMOVE_H

#include <iaggregate.h>
#include <imodelitem.h>
#include <imodellistwatcher.h>
#include <QList>

class ScopedItemRemove
{
    const IModelItem *_list;
    const int _index;
    QList<IModelListWatcher*> _watchers;

public:
    ScopedItemRemove(const IModelItem *list, int index)
        :   _list(list)
        ,   _index(index)
    {
        if (!_list)
            return;
        const QList<IComponent*> &components = query<IAggregate>(_list)->components();
        foreach (IComponent *component, components)
            if (component->isTypeOfInterface(I::IModelListWatcher))
                _watchers.append(query<IModelListWatcher>(component));
        foreach (IModelListWatcher *watcher, _watchers)
            watcher->beginRemoveItem(_list, index);
    }

    ~ScopedItemRemove()
    {
        if (!_list)
            return;
        foreach (IModelListWatcher *watcher, _watchers)
            watcher->endRemoveItem(_list, _index);
    }
};

#endif
