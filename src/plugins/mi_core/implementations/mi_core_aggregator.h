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

#ifndef MI_CORE_AGGREGATOR_H
#define MI_CORE_AGGREGATOR_H

#include "mi_iaggregator.h"

namespace Mi {
namespace Core {

class MI_CORE_EXPORT Aggregator : public IAggregator
{
    QHash<int, IAggregate*> _aggregates;

protected:
    Aggregator();
    ~Aggregator();

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        return 0;
    }

    IAggregate *appendAggregate(IAggregate *aggregate);
    void clear();

public:
    // IUnknown
    void *queryInterface(int interfaceType)
    {
        if (I::IAggregator == interfaceType)
            return this;
        IAggregate *interface = _aggregates.value(interfaceType);
        if (interface)
            return interface;
        return createAggregate(interfaceType);
    }

    const void *queryInterface(int interfaceType) const
    {
        if (I::IAggregator == interfaceType)
            return this;
        IAggregate *interface = _aggregates.value(interfaceType);
        if (interface)
            return interface;
        return 0;
    }
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_AGGREGATOR_H
