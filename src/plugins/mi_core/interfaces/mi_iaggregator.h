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

class IAggregator : public IUnknown
{
public:
    enum { InterfaceType = I::IAggregator };

    virtual IAggregate *createAggregate(int interfaceType) = 0;
    virtual IAggregate *appendAggregate(IAggregate *aggregate) = 0;
    virtual void clear() = 0;

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

#endif // MI_IAGGREGATOR_H
