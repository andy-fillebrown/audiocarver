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

#ifndef MI_CORE_SUBAGGREGATOR_H
#define MI_CORE_SUBAGGREGATOR_H

#include "mi_core_aggregator.h"

namespace Mi {
namespace Core {

class MI_CORE_EXPORT SubAggregator : public IAggregator
{
    friend class SuperAggregator;

    Aggregator *_superAggregator;

protected:
    SubAggregator()
    {}

    void setSuperAggregator(Aggregator *superAggregator)
    {
        _superAggregator = superAggregator;
    }

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        return 0;
    }

    IAggregate *appendAggregate(IAggregate *aggregate)
    {
        return _superAggregator->appendAggregate(aggregate);
    }

public:
    // IUnknown
    void *queryInterface(int interfaceType)
    {
        return _superAggregator->queryInterface(interfaceType);
    }

    const void *queryInterface(int interfaceType) const
    {
        return const_cast<const Aggregator*>(_superAggregator)->queryInterface(interfaceType);
    }
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_SUBAGGREGATOR_H
