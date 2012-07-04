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

#ifndef AC_FACTORY_H
#define AC_FACTORY_H

#include <mi_ifactory.h>

namespace Ac {
class Database;
} // namespace Ac

namespace Database {

class Factory : public IFactory
{
    friend class Ac::Database;

    Ac::Database *_aggregator;

protected:
    Ac::Database *a() const
    {
        return _aggregator;
    }

    Factory(Ac::Database *aggregator)
        :   _aggregator(aggregator)
    {}

    virtual IAggregate *init();

    // IFactory
    IAggregator *create(int itemType);

    // IAggregate
    IAggregator *aggregator() const;
};

} // namespace Database

#endif // AC_FACTORY_H
