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

#ifndef MI_AGGREGATOR_H
#define MI_AGGREGATOR_H

#include "mi_iaggregator.h"

#include <mi_iaggregate.h>

#include <QSharedPointer>

typedef QHash<int, AggregatePointer> InterfaceTypeToAggregateHash;

class MI_CORE_EXPORT Aggregator : public IAggregator
{
    InterfaceTypeToAggregateHash _aggregates;

protected:
    AggregateList aggregates() const
    {
        return _aggregates.values();
    }

    // IAggregator
    IAggregate *createAggregate(int interfaceType) { return 0; }

    IAggregate *appendAggregate(IAggregate *aggregate)
    {
        const int interface_type = aggregate->interfaceType();
        if (!_aggregates.contains(interface_type))
            _aggregates.insert(interface_type, AggregatePointer(aggregate));
        return aggregate;
    }

    void removeAggregate(IAggregate *aggregate)
    {
        _aggregates.remove(aggregate->interfaceType());
    }


public:
    void *queryInterface(int interfaceType);
    const void *queryInterface(int interfaceType) const;
};

#endif // MI_AGGREGATOR_H
