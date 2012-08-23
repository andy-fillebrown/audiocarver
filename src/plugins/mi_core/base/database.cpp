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

#include "database.h"
#include <interfaces/iaggregate.h>
#include <interfaces/isession.h>

static IDatabase *instance = 0;

IDatabase *IDatabase::instance()
{
    return ::instance;
}

namespace Base {

Database::Database()
{
    ISession::instance()->remove(::instance);
    delete ::instance;
    ::instance = this;
}

Database::~Database()
{
    ::instance = 0;
}

IUnknown *Database::initialize()
{
    return ISession::instance()->append(this);
}

void *Database::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<Database*>(this);
    return ISession::instance()->queryInterface(interfaceType);
}

}
