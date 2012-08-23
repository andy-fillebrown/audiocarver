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

#include "databaseobjectfactory.h"
#include <iaggregate.h>
#include <isession.h>

static IDatabaseObjectFactory *instance = 0;

IDatabaseObjectFactory *IDatabaseObjectFactory::instance()
{
    return ::instance;
}

namespace Base {

DatabaseObjectFactory::DatabaseObjectFactory()
{
    ISession::instance()->remove(::instance);
    delete ::instance;
    ::instance = this;
}

DatabaseObjectFactory::~DatabaseObjectFactory()
{
    ::instance = 0;
}

IUnknown *DatabaseObjectFactory::initialize()
{
    return ISession::instance()->append(this);
}

void *DatabaseObjectFactory::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<DatabaseObjectFactory*>(this);
    return ISession::instance()->queryInterface(interfaceType);
}

}
