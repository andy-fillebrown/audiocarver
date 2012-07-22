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

#include "mi_core_orphanage.h"

#include <mi_core_root.h>

static IOrphanage *instance = 0;

IOrphanage *IOrphanage::instance()
{
    return ::instance;
}

namespace Mi {
namespace Core {

Orphanage::Orphanage(Root *aggregator)
    :   IOrphanage(aggregator)
{
    if (::instance)
        delete ::instance;
    ::instance = this;
}

Orphanage::~Orphanage()
{
    ::instance = 0;
}

IAggregate *Orphanage::init()
{
    return this;
}

Root *Orphanage::aggregator() const
{
    return static_cast<Root*>(IAggregate::aggregator());
}

void Orphanage::append(IAggregator *orphan)
{
    QList<IAggregator*> &orphans = aggregator()->orphans();
    if (orphans.contains(orphan))
        return;
    orphans.append(orphan);
}

void Orphanage::remove(IAggregator *orphan)
{
    aggregator()->orphans().removeOne(orphan);
}

} // namespace Core
} // namespace Mi
