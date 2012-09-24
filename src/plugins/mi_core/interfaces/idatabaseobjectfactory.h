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

#ifndef IDATABASEOBJECTFACTORY_H
#define IDATABASEOBJECTFACTORY_H

#include <iunknown.h>
#include "mi_core_global.h"
#include "mi_core_interfaces.h"

class IAggregate;
class IModelItem;

class MI_CORE_EXPORT IDatabaseObjectFactory : public IUnknown
{
public:
    enum { InterfaceType = I::IDatabaseObjectFactory };

    static IDatabaseObjectFactory *instance();

    virtual IAggregate *create(int itemType, IModelItem *parent = 0) = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }
};

#endif
