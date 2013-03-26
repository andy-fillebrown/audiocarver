/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "mi_core_base_database.h"
#include <iaggregate.h>
#include <isession.h>

static IDatabase *instance = 0;

IDatabase *IDatabase::instance()
{
    return ::instance;
}

namespace Base {

Database::Database()
{
    IAggregate *aggregate = ISession::instance();
    aggregate->removeComponent(::instance);
    delete ::instance;
    ::instance = this;
    aggregate->appendComponent(this);
}

Database::~Database()
{
    ::instance = 0;
}

void *Database::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : ISession::instance()->queryInterface(interfaceType);
}

}
