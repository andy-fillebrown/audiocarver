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

#ifndef AC_CORE_DATABASE_CURVE_MODELITEM_H
#define AC_CORE_DATABASE_CURVE_MODELITEM_H

#include "mi_core_database_object_modelitem.h"

#include "ac_core_global.h"

namespace Ac {
namespace Core {
namespace Database {
namespace Curve {

class Aggregate;
typedef Mi::Core::Database::Object::ModelItem ModelItem_BaseClass;

class AC_CORE_EXPORT ModelItem : public ModelItem_BaseClass
{
protected:
    ModelItem(IAggregate *aggregate);
    IUnknown *initialize();
    bool isTypeOfItem(int itemType) const;
};

}
}
}
}

#endif
