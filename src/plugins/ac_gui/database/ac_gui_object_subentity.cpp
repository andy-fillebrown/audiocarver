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

#include "ac_gui_object_subentity.h"
#include <iaggregate.h>
#include <imodelitem.h>
#include <iparententity.h>

namespace Object {

void *SubEntity::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<SubEntity*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *SubEntity::initialize()
{
    aggregate()->append(this);
    return this;
}

IParentEntity *SubEntity::parent() const
{
    return query<IParentEntity>(query<IModelItem>(this)->parent());
}

}
