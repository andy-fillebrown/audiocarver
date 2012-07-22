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
    IAggregator *init();

    QList<IAggregate*> aggregates() const
    {
        return _aggregates.values();
    }

    // IAggregator
    void *setAggregate(int interfaceType, IAggregate *aggregate);

    void *setObject(int interfaceType, QObject *object)
    {
        return 0;
    }

    void clear()
    {}

public:
    // IUnknown
    void *queryInterface(int interfaceType) const;
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_AGGREGATOR_H
