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

#include "mi_aggregator.h"

#include <mi_iaggregate.h>

Aggregator::~Aggregator()
{
    qDeleteAll(_aggregates);
}

#define Q_MI_QUERYINTERFACE_DEFINITION \
    if (Mi::AggregatorInterface == interfaceType) \
        return this; \
    Aggregates::ConstIterator end = _aggregates.constEnd(); \
    for (Aggregates::ConstIterator i = _aggregates.constBegin();  i != end;  ++i) \
        if ((*i)->interfaceType() == interfaceType) \
            return *i; \
    for (Aggregates::ConstIterator i = _aggregates.constBegin();  i != end;  ++i) \
        if ((*i)->isTypeOfInterface(interfaceType)) \
            return *i; \

bool Aggregator::containsAggregate(int interfaceType) const
{
    Q_MI_QUERYINTERFACE_DEFINITION
    return false;
}

void *Aggregator::queryInterface(int interfaceType)
{
    Q_MI_QUERYINTERFACE_DEFINITION
    return createAggregate(interfaceType);
}

const void *Aggregator::queryInterface(int interfaceType) const
{
    Q_MI_QUERYINTERFACE_DEFINITION
    return 0;
}
