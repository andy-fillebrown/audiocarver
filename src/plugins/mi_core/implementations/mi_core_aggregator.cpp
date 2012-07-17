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

#include "mi_core_aggregator.h"

#include <mi_iaggregate.h>
#include <mi_idatabase.h>
#include <mi_iorphanage.h>

namespace Mi {
namespace Core {

Aggregator::Aggregator()
{
    IOrphanage *orphanage = query<IOrphanage>(IDatabase::instance());
    if (orphanage)
        orphanage->append(this);
}

Aggregator::~Aggregator()
{
    IOrphanage *orphanage = query<IOrphanage>(IDatabase::instance());
    if (orphanage)
        orphanage->remove(this);
    clear();
}

IAggregate *Aggregator::appendAggregate(IAggregate *aggregate)
{
    const int interface_type = aggregate->interfaceType();
    if (!_aggregates.contains(interface_type))
        _aggregates.insert(interface_type, aggregate);
    return aggregate;
}

void Aggregator::removeAggregate(IAggregate *aggregate)
{
    _aggregates.remove(aggregate->interfaceType());
}

void Aggregator::clear()
{
    qDeleteAll(_aggregates);
    _aggregates.clear();
}

} // namespace Core
} // namespace Mi
