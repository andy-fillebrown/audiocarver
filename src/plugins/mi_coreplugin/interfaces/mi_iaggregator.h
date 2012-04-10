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

class IAggregate;

template <typename T> class QSharedPointer;

typedef QSharedPointer<IAggregate> AggregatePointer;
typedef QList<AggregatePointer> AggregateList;

class IAggregator : public IUnknown
{
public:
    enum { InterfaceType = Mi::AggregatorInterface };

    virtual AggregateList aggregates() const = 0;
    virtual bool containsAggregate(int interfaceType) const = 0;
    virtual void *createAggregate(int interfaceType) = 0;
    virtual void *appendAggregate(IAggregate* aggregate) = 0;
    virtual void removeAggregate(IAggregate *aggregate) = 0;
    virtual void *queryInterface(int interfaceType) = 0;
    virtual const void *queryInterface(int interfaceType) const = 0;

    // IUnknown

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

template <> inline
QObject *query(IAggregator *aggregator)
{
    return aggregator ? cast<QObject>(aggregator->queryInterface(Mi::ObjectInterface)) : 0;
}

#endif // MI_IAGGREGATE_H
