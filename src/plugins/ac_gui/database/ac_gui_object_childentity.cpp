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

#include "ac_gui_object_childentity.h"
#include <iaggregate.h>
#include <imodelitem.h>
#include <iparententity.h>

namespace Object {

IUnknown *ChildEntity::initialize()
{
    aggregate()->append(this);
    return this;
}

void *ChildEntity::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ChildEntity*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IParentEntity *ChildEntity::parent() const
{
    IModelItem *parent = query<IModelItem>(this)->parent();
    if (parent && parent->isList())
        parent = parent->parent();
    return query<IParentEntity>(parent);
}

}
