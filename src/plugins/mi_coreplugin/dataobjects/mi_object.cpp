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
#include <mi_listobject.h>
#include <QMetaProperty>
#include <QVariant>

void MiObjectPrivate::notifyParentOfChange(int i)
{
    Q_UNUSED(i);
    MiObject *parent = q_ptr->parent();
    if (parent)
        parent->d_ptr->endChange(i);
}

QString MiObject::propertyType(int i) const
{
    return metaObject()->property(i).typeName();
}

QString MiObject::propertyName(int i) const
{
    return metaObject()->property(i).name();
}

bool MiObject::isPropertyWritable(int i) const
{
    return metaObject()->property(i).isWritable();
}

QVariant MiObject::propertyValue(int i) const
{
    return metaObject()->property(i).read(this);
}

void MiObject::setPropertyValue(int i, const QVariant &value)
{
    const QMetaObject *metaObj = metaObject();
    if (!metaObj->property(i).write(this, value) && value.isValid())
        metaObj->property(i).write(this, QVariant());
}

MiObject *MiObject::parent() const
{
    return qobject_cast<MiObject*>(QObject::parent());
}
