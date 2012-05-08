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

#ifndef AC_DATABASE_OBJECTGUIFACTORY_H
#define AC_DATABASE_OBJECTGUIFACTORY_H

#include "ac_database_objectfactory.h"

namespace Database {

class ObjectGuiFactory : public ObjectFactory
{
protected:
    // IDataObjectFactory
    IAggregator *createObject(int itemType);

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

} // namespace Database

#endif // AC_DATABASE_OBJECTGUIFACTORY_H
