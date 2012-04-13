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

#ifndef MI_IAGGREGATOR_H
#define MI_IAGGREGATOR_H

#include "mi_iunknown.h"

#include <mi_interfacedefinitions.h>

class IAggregate;

template <typename T> class QSharedPointer;

typedef QSharedPointer<IAggregate> AggregatePointer;
typedef QList<AggregatePointer> AggregateList;

class IAggregator : public IUnknown
{
public:
    Q_I_BASE__UNKNOWN__INTERFACE_TYPE(IAggregator)

    virtual AggregateList aggregates() const = 0;
    virtual IAggregate *createAggregate(int interfaceType) = 0;
    virtual IAggregate *appendAggregate(IAggregate* aggregate) = 0;
    virtual void removeAggregate(IAggregate *aggregate) = 0;
};

#endif // MI_IAGGREGATE_H
