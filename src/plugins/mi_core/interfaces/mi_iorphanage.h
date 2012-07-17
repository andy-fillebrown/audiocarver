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

#ifndef MI_IORPHANAGE_H
#define MI_IORPHANAGE_H

#include "mi_iaggregate.h"

class IAggregator;

class MI_CORE_EXPORT IOrphanage : public IAggregate
{
public:
    enum { InterfaceType = I::IOrphanage };

    virtual void append(IAggregator *aggregator) = 0;
    virtual void remove(IAggregator *aggregator) = 0;

    // IUnknown
    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IAggregate::isTypeOfInterface(interfaceType);
    }
};

#endif // MI_IORPHANAGE_H