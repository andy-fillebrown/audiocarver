/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "object.h"
#include <icomponent.h>

using namespace Aggregation;
using namespace Database;

void Object::addComponent(IComponent *component)
{
    Aggregate *aggregate = query<Aggregate>();
    if (!aggregate) {
        aggregate = new Aggregate;
        aggregate->add(this);
    }
    aggregate->add(component);
}

void Object::setId(const QString &id_)
{
    if (id_ == id())
        return;

    // Get parent component.

    // If id is in use, generate a new one.

    // Add id to parent's id map.

    // Return the id added to parent's id map (id is not always the one passed in).
}
