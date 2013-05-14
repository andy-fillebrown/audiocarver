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

#ifndef MI_CORE_BASE_DATABASEOBJECTFACTORY_H
#define MI_CORE_BASE_DATABASEOBJECTFACTORY_H

#include <idatabaseobjectfactory.h>

class IAggregate;

namespace Base {

class MI_CORE_EXPORT DatabaseObjectFactory : public IDatabaseObjectFactory
{
protected:
    DatabaseObjectFactory()
    {
        IAggregate *aggregate = ISession::instance();
        IDatabaseObjectFactory *instance = IDatabaseObjectFactory::instance();
        aggregate->removeComponent(instance);
        delete instance;
        aggregate->appendComponent(this);
    }

    void *queryInterface(int interfaceType) const
    {
        void *i = IComponent::queryInterface(interfaceType);
        return i ? i : ISession::instance()->queryInterface(interfaceType);
    }

    void initialize()
    {}

    void reset()
    {}
};

}

#endif
