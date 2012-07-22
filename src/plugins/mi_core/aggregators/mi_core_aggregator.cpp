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
#include <mi_iorphanage.h>

namespace Mi {
namespace Core {

Aggregator::Aggregator()
{
    IOrphanage *orphanage = IOrphanage::instance();
    if (orphanage)
        orphanage->append(this);
}

Aggregator::~Aggregator()
{
    IOrphanage *orphanage = IOrphanage::instance();
    if (orphanage)
        orphanage->remove(this);
    qDeleteAll(_aggregates);
    _aggregates.clear();
}

IAggregator *Aggregator::init()
{
    return this;
}

void *Aggregator::setAggregate(int interfaceType, IAggregate *aggregate)
{
    _aggregates.insert(interfaceType, aggregate);
    return aggregate;
}

void *Aggregator::queryInterface(int interfaceType) const
{
    return _aggregates.value(interfaceType);
}

} // namespace Core
} // namespace Mi
