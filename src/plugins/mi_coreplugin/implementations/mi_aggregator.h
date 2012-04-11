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

typedef QHash<IAggregate*, AggregatePointer> AggregateHash;

class MI_CORE_EXPORT Aggregator : public IAggregator
{
    AggregateHash _aggregates;

protected:
    AggregateList aggregates() const
    {
        return _aggregates.values();
    }

    // IAggregator

    bool containsAggregate(int interfaceType) const;

    void *appendAggregate(IAggregate *aggregate)
    {
        if (!_aggregates.contains(aggregate))
            _aggregates.insert(aggregate, AggregatePointer(aggregate));
        return aggregate;
    }

    void removeAggregate(IAggregate *aggregate)
    {
        _aggregates.remove(aggregate);
    }

public:
    void *queryInterface(int interfaceType);
    const void *queryInterface(int interfaceType) const;
};

#endif // MI_AGGREGATOR_H
