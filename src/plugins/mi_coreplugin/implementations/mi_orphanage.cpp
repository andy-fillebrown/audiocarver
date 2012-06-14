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

#include "mi_orphanage.h"

#include <mi_iaggregator.h>

static IOrphanage *instance = 0;

IOrphanage *IOrphanage::instance()
{
    return ::instance;
}

void Orphanage::destroy()
{
    delete ::instance;
    ::instance = 0;
}

Orphanage::Orphanage()
{
    if (::instance)
        delete ::instance;
    ::instance = this;
}

Orphanage::~Orphanage()
{
    qDeleteAll(_orphans);
    _orphans.clear();
}

void Orphanage::append(IAggregator *aggregator)
{
    if (_orphans.contains(aggregator))
        return;
    _orphans.append(aggregator);
}

void Orphanage::remove(IAggregator *aggregator)
{
    _orphans.removeOne(aggregator);
}
