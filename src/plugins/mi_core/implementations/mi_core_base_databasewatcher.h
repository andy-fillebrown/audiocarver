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

#ifndef MI_CORE_BASE_DATABASEWATCHER_H
#define MI_CORE_BASE_DATABASEWATCHER_H

#include <idatabasewatcher.h>
#include "mi_core_global.h"

class IAggregate;

namespace Base {

class MI_CORE_EXPORT DatabaseWatcher : public IDatabaseWatcher
{
    IAggregate *_aggregate;

protected:
    DatabaseWatcher(IAggregate *aggregate);

    void *queryInterface(int interfaceType) const;

    void initialize()
    {}

    void reset()
    {}

    void beginRead(IDatabase *database)
    {}

    void endRead(IDatabase *database)
    {}

    void beginWrite(IDatabase *database)
    {}

    void endWrite(IDatabase *database)
    {}
};

}

#endif
