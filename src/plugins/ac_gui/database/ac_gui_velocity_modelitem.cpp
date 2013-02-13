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

#include "ac_gui_velocity_modelitem.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>

using namespace Ac;

namespace Velocity {

IUnknown *ModelItem::initialize()
{
    return Object::ModelItem::initialize();
}

int ModelItem::itemType() const
{
    return VelocityItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (VelocityItem == itemType)
        return true;
    return Object::ModelItem::isTypeOfItem(itemType);
}

IModelItem *ModelItem::findItem(int itemType) const
{
    if (GripsItem == itemType)
        return query<IModelItem>(grips());
    return Object::ModelItem::findItem(itemType);
}

}
