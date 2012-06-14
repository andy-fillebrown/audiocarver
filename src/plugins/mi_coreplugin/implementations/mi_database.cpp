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

#include "mi_database.h"

#include <mi_iaggregate.h>

static IDatabase *instance = 0;

IDatabase *IDatabase::instance()
{
    return ::instance;
}

namespace Mi {

void Database::destroy()
{
    delete ::instance;
    ::instance = 0;
}

Database::Database()
{
    if (::instance)
        delete ::instance;
    ::instance = this;
}

IAggregator *Database::init()
{
    return this;
}

Database::~Database()
{
    clear();
}

IAggregate *Database::appendAggregate(IAggregate *aggregate)
{
    const int interface_type = aggregate->interfaceType();
    if (!_aggregates.contains(interface_type))
        _aggregates.insert(interface_type, aggregate);
    return aggregate;
}

void Database::removeAggregate(IAggregate *aggregate)
{
    _aggregates.remove(aggregate->interfaceType());
}

void Database::clear()
{
    qDeleteAll(_aggregates);
    _aggregates.clear();
}

IAggregate *Database::Orphanage::init()
{
    return this;
}

} // namespace Mi
