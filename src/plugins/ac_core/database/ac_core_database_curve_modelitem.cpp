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

#include "ac_core_database_curve_modelitem.h"

#include "ac_core_database_curve_aggregate.h"
#include "ac_core_namespace.h"
#include "ac_core_point.h"

namespace Ac {
namespace Core {
namespace Database {
namespace Curve {

ModelItem::ModelItem(IAggregate *aggregate)
    :   ModelItem_BaseClass(aggregate)
{
    Q_ASSERT(dynamic_cast<Aggregate*>(aggregate));
}

IUnknown *ModelItem::initialize()
{
    return ModelItem_BaseClass::initialize();
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (CurveItem == itemType)
        return true;
    return ModelItem_BaseClass::isTypeOfItem(itemType);
}

}
}
}
}
