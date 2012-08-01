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

#ifndef AC_CORE_DATABASE_OBJECTLIST_AGGREGATE_H
#define AC_CORE_DATABASE_OBJECTLIST_AGGREGATE_H

#include "mi_core_database_objectlist_aggregate.h"

#include <ac_core_global.h>

namespace Ac {
namespace Core {

namespace Session {
    class ClassFactory;
}

namespace Database {
namespace ObjectList {

typedef Mi::Core::Database::ObjectList::Aggregate Aggregate_BaseClass;

class AC_CORE_EXPORT Aggregate : public Aggregate_BaseClass
{
    friend class Session::ClassFactory;

protected:
    Aggregate(int listType = Mi::UnknownItem)
        :   Aggregate_BaseClass(listType)
    {}

    IAggregate *initialize();
};

}
}
}
}

#endif
