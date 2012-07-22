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

#include "mi_core_model.h"

#include <ac_core_global.h>

class QAbstractItemModel;

namespace Ac {
namespace Core {

class Database;

class AC_CORE_EXPORT Model : public Mi::Core::Model
{
    friend class Database;

protected:
    Model(Database *aggregator);

    IAggregate *init();
    Database *a() const;

    // IModel
    Mi::Core::QDataModel *q() const;
    IModelItem *rootItem() const;
    void beginChangeData(const IModelData *data, int role, int dataChangeType);
    void endChangeData(const IModelData *data, int role, int dataChangeType);
    void beginChangeParent(const IModelItem *item);
    void endChangeParent(const IModelItem *item);
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_MODEL_H
