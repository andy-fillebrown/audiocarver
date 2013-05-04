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

#ifndef MI_CORE_SCOPEDSELECTIONCHANGE_H
#define MI_CORE_SCOPEDSELECTIONCHANGE_H

#include <iaggregate.h>
#include <icomponent.h>
#include <iselectionsetwatcher.h>
#include <QList>

class ScopedSelectionChange
{
    ISelectionSet *_ss;
    QList<ISelectionSetWatcher*> _watchers;

public:
    ScopedSelectionChange(ISelectionSet *ss)
        :   _ss(ss)
    {
        if (!_ss)
            return;
        const QList<IComponent*> &components = query<IAggregate>(_ss)->components();
        foreach (IComponent *component, components)
            if (component->isTypeOfInterface(I::ISelectionSetWatcher))
                _watchers.append(query<ISelectionSetWatcher>(component));
        foreach (ISelectionSetWatcher *watcher, _watchers)
            watcher->beginChangeSelection(_ss);
    }

    ~ScopedSelectionChange()
    {
        if (!_ss)
            return;
        foreach (ISelectionSetWatcher *watcher, _watchers)
            watcher->endChangeSelection(_ss);
    }
};

#endif
