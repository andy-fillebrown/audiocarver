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

#include "mi_core_superaggregator.h"

#include <mi_core_subaggregator.h>

namespace Mi {
namespace Core {

SuperAggregator::~SuperAggregator()
{
    qDeleteAll(_subAggregators);
    _subAggregators.clear();
}

IAggregate *SuperAggregator::createAggregate(int interfaceType)
{
    foreach (IAggregator *sub_aggregator, _subAggregators) {
        IAggregate *aggregate = sub_aggregator->createAggregate(interfaceType);
        if (aggregate)
            return aggregate;
    }
    return 0;
}

void SuperAggregator::appendSubAggregator(SubAggregator *subAggregator)
{
    if (_subAggregators.contains(subAggregator))
        return;
    _subAggregators.append(subAggregator);
    subAggregator->setSuperAggregator(this);
}

} // namespace Core
} // namespace Mi
