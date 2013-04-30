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

#ifndef AC_GUI_DATABASE_GRAPHICSVIEWMANAGERUPDATER_H
#define AC_GUI_DATABASE_GRAPHICSVIEWMANAGERUPDATER_H

#include "mi_core_base_databasewatcher.h"

namespace Database {

class GraphicsViewManagerUpdater : public Base::DatabaseWatcher
{
public:
    GraphicsViewManagerUpdater(IAggregate *aggregate)
        :   Base::DatabaseWatcher(aggregate)
    {}

protected:
    void beginRead(const IDatabase *database);
    void endRead(const IDatabase *database);
    void beginWrite(const IDatabase *database);
};

}

#endif