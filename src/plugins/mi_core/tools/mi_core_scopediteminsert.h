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

#ifndef MI_CORE_SCOPEDITEMINSERT_H
#define MI_CORE_SCOPEDITEMINSERT_H

#include <iaggregate.h>
#include <imodelitem.h>
#include <imodelitemlistwatcher.h>
#include <QList>

class ScopedItemInsert
{
    const IModelItemList *_list;
    const int _index;
    QList<IModelItemListWatcher*> _watchers;

public:
    ScopedItemInsert(const IModelItemList *list, int index)
        :   _list(list)
        ,   _index(index)
    {
        if (!_list)
            return;
        const QList<IUnknown*> &components = query<IAggregate>(_list)->components();
        foreach (IUnknown *component, components)
            if (component->isTypeOfInterface(I::IModelItemListWatcher))
                _watchers.append(query<IModelItemListWatcher>(component));
        foreach (IModelItemListWatcher *watcher, _watchers)
            watcher->beginInsertItem(_list, index);
    }

    ~ScopedItemInsert()
    {
        if (!_list)
            return;
        foreach (IModelItemListWatcher *watcher, _watchers)
            watcher->endInsertItem(_list, _index);
    }
};

#endif
