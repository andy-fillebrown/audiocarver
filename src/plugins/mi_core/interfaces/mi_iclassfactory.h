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

#ifndef MI_ICLASSFACTORY_H
#define MI_ICLASSFACTORY_H

#include "mi_iunknown.h"

class IAggregate;
class IModelItem;

class IClassFactory : public IUnknown
{
public:
    enum { InterfaceType = I::IClassFactory };

    virtual IAggregate *createAggregate(int itemType, IModelItem *parent = 0) = 0;
    virtual IUnknown *createComponent(int interfaceType, IAggregate *aggregate) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif // MI_ICLASSFACTORY_H
