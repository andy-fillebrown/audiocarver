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

#define Q_QUERYINTERFACE_DEFINITION \
    if (Mi::AggregatorInterface == interfaceType) \
        return this; \
    AggregateHash::ConstIterator end = _aggregates.constEnd(); \
    for (AggregateHash::ConstIterator i = _aggregates.constBegin();  i != end;  ++i) \
        if ((*i)->interfaceType() == interfaceType) \
            return qGetPtrHelper(*i); \
    for (AggregateHash::ConstIterator i = _aggregates.constBegin();  i != end;  ++i) \
        if ((*i)->isTypeOfInterface(interfaceType)) \
            return qGetPtrHelper(*i); \

bool Aggregator::containsAggregate(int interfaceType) const
{
    Q_QUERYINTERFACE_DEFINITION
    return false;
}

void *Aggregator::queryInterface(int interfaceType)
{
    Q_QUERYINTERFACE_DEFINITION
    return createAggregate(interfaceType);
}

const void *Aggregator::queryInterface(int interfaceType) const
{
    Q_QUERYINTERFACE_DEFINITION
    return 0;
}
