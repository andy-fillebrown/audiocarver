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

#ifndef AC_DATABASE_H
#define AC_DATABASE_H

#include "mi_database.h"

#include "mi_ifactory.h"
#include "mi_ifiler.h"
#include "mi_imodel.h"

#include <ac_coreglobal.h>

namespace Ac {

class Database : public Mi::Database
{
    friend class CorePlugin;

    IAggregator *_score;

protected:
    Database()
    {}

    IAggregator *init();
    ~Database();

    IAggregator *score() const
    {
        return _score;
    }

    const QString &fileExtension() const;
    const QString &fileFilter() const;
    QString fileName() const;
    void reset();
    void read(const QString &fileName);
    void write(const QString &fileName);
    bool isReading() const;

    // IAggregator
    inline IAggregate *createAggregate(int interfaceType);
};

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
    IAggregator *create(int itemType);

    // IAggregate
    IAggregator *aggregator() const
    {
        return _aggregator;
    }
};

class Model : public IModel
{
    friend class Ac::Database;

    Ac::Database *_aggregator;

protected:
    Ac::Database *a() const
    {
        return _aggregator;
    }

    Model(Ac::Database *aggregator)
        :   _aggregator(aggregator)
    {}

    virtual IAggregate *init();

    // IModel
    void beginChangeData(const IModelData *data, int role);
    void endChangeData(const IModelData *data, int role);
    void beginChangeParent(const IModelItem *item);
    void endChangeParent(const IModelItem *item);

    // IAggregate
    IAggregator *aggregator() const
    {
        return _aggregator;
    }
};

} // namespace Database

inline IAggregate *Ac::Database::createAggregate(int interfaceType)
{
    switch (interfaceType) {
    case I::IFactory:
        return appendAggregate((new ::Database::Factory(this))->init());
    case I::IModel:
        return appendAggregate((new ::Database::Model(this))->init());
    default:
        return 0;
    }
}


#endif // AC_DATABASE_H
