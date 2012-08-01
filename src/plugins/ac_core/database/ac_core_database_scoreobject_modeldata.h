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

#ifndef AC_CORE_DATABASE_SCOREOBJECT_MODELDATA_H
#define AC_CORE_DATABASE_SCOREOBJECT_MODELDATA_H

#include <mi_core_database_object_modeldata.h>

#include <mi_imodelitemlist.h>

#include "ac_core_global.h"

namespace Ac {
namespace Core {
namespace Database {
namespace ScoreObject {

class Aggregate;
typedef Mi::Core::Database::Object::ModelData ModelData_BaseClass;

class AC_CORE_EXPORT ModelData : public ModelData_BaseClass
{
    friend class Aggregate;

    Aggregate *aggregate() const;

protected:
    ModelData(IAggregate *aggregate);
    IUnknown *initialize();

    int roleCount() const;
    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(const QVariant &value, int role);
};

}
}
}
}

#endif
