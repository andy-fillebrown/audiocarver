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

#ifndef AC_MODEL_H
#define AC_MODEL_H

#include <ac_coreglobal.h>

#include <mi_imodel.h>

namespace Ac {
class Database;
} // namespace Ac

class IModelItem;

namespace Database {

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
    IModelItem *rootItem() const;
    void beginChangeData(const IModelData *data, int role);
    void endChangeData(const IModelData *data, int role);
    void beginChangeParent(const IModelItem *item);
    void endChangeParent(const IModelItem *item);

    // IAggregate
    IAggregator *aggregator() const;
};

} // namespace Database

#endif // AC_MODEL_H
