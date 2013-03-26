/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "mi_core_base_aggregate.h"

namespace Base {

Aggregate::~Aggregate()
{
    qDeleteAll(_components);
    _components.clear();
}

void Aggregate::initialize()
{
    foreach (IComponent *component, _components)
        component->initialize();
}

void *Aggregate::queryInterface(int interfaceType) const
{
    foreach (IComponent *component, _components)
        if (component->isTypeOfInterface(interfaceType))
            return component->queryInterface(interfaceType);
    return IAggregate::queryInterface(interfaceType);
}

}
