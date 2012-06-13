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

#ifndef AC_DATABASE_FACTORY_H
#define AC_DATABASE_FACTORY_H

#include "mi_ifactory.h"

#include <ac_coreglobal.h>

class AcCorePlugin;

namespace Database {

class Factory : public IFactory
{
    friend class ::AcCorePlugin;

public:
    static IFactory *instance();

protected:
    Factory();

    // IFactory
    IAggregator *createItem(int itemType);
    IAggregator *createList(int itemType, int listType = Mi::ListItem);

    // IUnknown
    void *queryInterface(int interfaceType)
    {
        if (this->isTypeOfInterface(interfaceType))
            return this;
        return 0;
    }

    const void *queryInterface(int interfaceType) const
    {
        if (this->isTypeOfInterface(interfaceType))
            return this;
        return 0;
    }
};

} // namespace Database

#endif // AC_DATABASE_FACTORY_H
