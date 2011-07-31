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

#include "ac_parentgraphicsitem.h"
#include <mi_parentobject.h>

MiObject *AcParentGraphicsItem::dataObject() const
{
    Q_D(const AcParentGraphicsItem);
    return d->dataObject;
}

void AcParentGraphicsItem::setDataObject(MiParentObject *object)
{
    Q_D(AcParentGraphicsItem);
    if (d->dataObject == object)
        return;
    AcAbstractGraphicsItem::setDataObject(object);
    if (object) {
        Q_CONNECT(object, SIGNAL(updated(MiObject::ChangeFlags)), this, SLOT(updateDataObject(MiObject::ChangeFlags)));
        for (int i = 1;  i < MiObject::LastChangeFlag;  i *= 2)
            updateDataObject(MiObject::ChangeFlags(i));
    }
}
