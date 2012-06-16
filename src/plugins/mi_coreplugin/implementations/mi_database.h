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

#ifndef MI_DATABASE_H
#define MI_DATABASE_H

#include "mi_idatabase.h"

#include "mi_iorphanage.h"

namespace Mi {

class MI_CORE_EXPORT Database : public IDatabase
{
    friend class CorePlugin;

    static IDatabase *instance()
    {
        return IDatabase::instance();
    }

    static void destroy();

    QHash<int, IAggregate*> _aggregates;
    QList<IAggregator*> _orphans;

protected:
    Database();
    virtual IAggregator *init();
    virtual ~Database();

    QList<IAggregator*> &orphans()
    {
        return _orphans;
    }

    class Orphanage : public IOrphanage
    {
        friend class Database;

        Database *_aggregator;

    protected:
        Database *a() const
        {
            return _aggregator;
        }

        Orphanage(Database *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

        // IOrphanage
        void append(IAggregator *aggregator)
        {
            QList<IAggregator*> &orphans = a()->orphans();
            if (orphans.contains(aggregator))
                return;
            orphans.append(aggregator);
        }

        void remove(IAggregator *aggregator)
        {
            a()->orphans().removeOne(aggregator);
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    // IAggregator
    QList<IAggregate*> aggregates() const
    {
        return _aggregates.values();
    }

    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IOrphanage:
            return (new Orphanage(this))->init();
        default:
            return 0;
        }
    }

    IAggregate *appendAggregate(IAggregate *aggregate);
    void removeAggregate(IAggregate *aggregate);
    void clear();

public:
    // IUnknown
    void *queryInterface(int interfaceType)
    {
        if (I::IAggregator == interfaceType)
            return this;
        IAggregate *interface = _aggregates.value(interfaceType);
        if (interface)
            return interface;
        return createAggregate(interfaceType);
    }

    const void *queryInterface(int interfaceType) const
    {
        if (I::IAggregator == interfaceType)
            return this;
        IAggregate *interface = _aggregates.value(interfaceType);
        if (interface)
            return interface;
        return 0;
    }
};

} // namespace Mi

#endif // MI_DATABASE_H
