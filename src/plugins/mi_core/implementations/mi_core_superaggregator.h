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

#ifndef MI_CORE_SUPERAGGREGATOR_H
#define MI_CORE_SUPERAGGREGATOR_H

#include "mi_core_aggregator.h"

namespace Mi {
namespace Core {

class MI_CORE_EXPORT SuperAggregator : public Aggregator
{
    QList<IAggregator*> _aggregators;

protected:
    SuperAggregator()
    {}

    ~SuperAggregator();

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        foreach (IAggregator *aggregator, _aggregators) {
            IAggregate *aggregate = aggregator->createAggregate(interfaceType);
            if (aggregate)
                return appendAggregate(aggregate);
        }
        return 0;
    }

public:
    void appendAggregator(IAggregator *aggregator)
    {
        if (_aggregators.contains(aggregator))
            return;
        _aggregators.append(aggregator);
    }

    void removeAggregator(IAggregator *aggregator)
    {
        _aggregators.removeOne(aggregator);
    }
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_SUPERAGGREGATOR_H
