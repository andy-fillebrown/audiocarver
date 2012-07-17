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

#ifndef AC_CORE_OBJECTFACTORY_H
#define AC_CORE_OBJECTFACTORY_H

#include <mi_iobjectfactory.h>

namespace Ac {
namespace Core {

class Database;

class ObjectFactory : public IObjectFactory
{
    friend class Database;

    Database *_aggregator;

protected:
    Database *a() const
    {
        return _aggregator;
    }

    ObjectFactory(Database *aggregator)
        :   _aggregator(aggregator)
    {}

    virtual IAggregate *init();

    // IFactory
    IAggregator *create(int itemType);

    // IAggregate
    IAggregator *aggregator() const;
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_OBJECTFACTORY_H