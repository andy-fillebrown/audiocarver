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

#ifndef AC_DATAOBJECTFACTORY_H
#define AC_DATAOBJECTFACTORY_H

#include "mi_idataobjectfactory.h"

#include <ac_coreglobal.h>

class AC_CORE_EXPORT DataObjectFactory : public IDataObjectFactory
{
protected:
    IAggregator *createObject(int itemType);
    IAggregator *createObjectList(int itemType, int listType = Mi::ListItem);

public:
    // IUnknown
    void *queryInterface(int interfaceType)
    {
        return this->isTypeOfInterface(interfaceType) ? this : 0;
    }

    const void *queryInterface(int interfaceType) const
    {
        return this->isTypeOfInterface(interfaceType) ? this : 0;
    }
};

#endif // AC_DATAOBJECTFACTORY_H
