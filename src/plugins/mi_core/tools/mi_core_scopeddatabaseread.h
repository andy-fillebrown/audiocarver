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

#ifndef MI_CORE_SCOPEDDATABASEREAD_H
#define MI_CORE_SCOPEDDATABASEREAD_H

#include <iaggregate.h>
#include <idatabase.h>
#include <idatabasewatcher.h>
#include <QList>

class ScopedDatabaseRead
{
    IDatabase *_database;
    QList<IDatabaseWatcher*> _watchers;

public:
    ScopedDatabaseRead(IDatabase *database)
        :   _database(database)
    {
        if (!_database)
            return;
        const QList<IComponent*> &components = query<IAggregate>(_database)->components();
        foreach (IComponent *component, components)
            if (component->isTypeOfInterface(I::IDatabaseWatcher))
                _watchers.append(query<IDatabaseWatcher>(component));
        foreach (IDatabaseWatcher *watcher, _watchers)
            watcher->beginRead(_database);
    }

    ~ScopedDatabaseRead()
    {
        if (!_database)
            return;
        foreach (IDatabaseWatcher *watcher, _watchers)
            watcher->endRead(_database);
    }
};

#endif
