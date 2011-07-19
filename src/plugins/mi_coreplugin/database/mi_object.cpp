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

#include "mi_object.h"
#include <aggregate.h>
#include <mi_database.h>
#include <mi_propertybag.h>

using namespace Aggregation;
using namespace Private;

MiDatabase *MiObject::database() const
{
    if (isDatabase())
        return qobject_cast<MiDatabase*>(const_cast<MiObject*>(this));
    MiObject *parent = qobject_cast<MiObject*>(this->parent());
    if (parent)
        return parent->database();
    return 0;
}

void MiObject::beginChangeProperty(int propertyIndex)
{
    MiPropertyBag *pb = query<MiPropertyBag>(this);
    if (!pb)
        return;
    pb->emit propertyAboutToBeChanged(pb->propertyValue(propertyIndex), propertyIndex);
}

void MiObject::endChangeProperty(int propertyIndex)
{
    MiPropertyBag *pb = query<MiPropertyBag>(this);
    if (!pb)
        return;
    pb->emit propertyChanged(pb->propertyValue(propertyIndex), propertyIndex);
}
