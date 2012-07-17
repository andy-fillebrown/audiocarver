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

class SubAggregator;

class MI_CORE_EXPORT SuperAggregator : public Aggregator
{
    QList<IAggregator*> _subAggregators;

protected:
    SuperAggregator()
    {}

    ~SuperAggregator();

    // IAggregator
    IAggregate *createAggregate(int interfaceType);

public:
    void appendSubAggregator(SubAggregator *subAggregator);
};

} // namespace Core
} // namespace Mi

#endif // MI_CORE_SUPERAGGREGATOR_H
