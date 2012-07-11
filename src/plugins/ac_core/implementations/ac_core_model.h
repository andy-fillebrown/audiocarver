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

#ifndef AC_CORE_MODEL_H
#define AC_CORE_MODEL_H

#include <mi_imodel.h>

namespace Ac {
namespace Core {

class Database;

class Model : public IModel
{
    friend class Database;

    Database *_aggregator;

protected:
    Database *a() const
    {
        return _aggregator;
    }

    Model(Database *aggregator)
        :   _aggregator(aggregator)
    {}

    virtual IAggregate *init();

    // IModel
    IModelItem *rootItem() const;
    void beginChangeData(const IModelData *data, int role, Mi::DataChangeType dataChangeType);
    void endChangeData(const IModelData *data, int role, Mi::DataChangeType dataChangeType);
    void beginChangeParent(const IModelItem *item);
    void endChangeParent(const IModelItem *item);

    // IAggregate
    IAggregator *aggregator() const;
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_MODEL_H
