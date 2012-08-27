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
#include <imodelitemwatcher.h>
#include <QList>

class ScopedItemInsert
{
    const IModelItem *_parent;
    const int _index;
    QList<IModelItemWatcher*> _watchers;

public:
    ScopedItemInsert(const IModelItem *parent, int index)
        :   _parent(parent)
        ,   _index(index)
    {
        if (!_parent)
            return;
        const QList<IUnknown*> &components = query<IAggregate>(_parent)->components();
        foreach (IUnknown *component, components)
            if (component->isTypeOfInterface(I::IModelItemWatcher))
                _watchers.append(query<IModelItemWatcher>(component));
        foreach (IModelItemWatcher *watcher, _watchers)
            watcher->beginInsertItem(_parent, index);
    }

    ~ScopedItemInsert()
    {
        if (!_parent)
            return;
        foreach (IModelItemWatcher *watcher, _watchers)
            watcher->endInsertItem(_parent, _index);
    }
};

#endif
