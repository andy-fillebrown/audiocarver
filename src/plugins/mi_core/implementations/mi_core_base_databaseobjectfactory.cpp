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

#include "mi_core_base_databaseobjectfactory.h"
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
    IAggregate *aggregate = ISession::instance();
    aggregate->remove(::instance);
    delete ::instance;
    ::instance = this;
    aggregate->append(this);
}

DatabaseObjectFactory::~DatabaseObjectFactory()
{
    ::instance = 0;
}

void *DatabaseObjectFactory::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : ISession::instance()->queryInterface(interfaceType);
}

}