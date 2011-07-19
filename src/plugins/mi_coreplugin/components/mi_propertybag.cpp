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

#include "mi_propertybag.h"
#include <QMetaProperty>

QString MiPropertyBag::className() const
{
    return d->object->metaObject()->className();
}

int MiPropertyBag::propertyCount() const
{
    return d->object->metaObject()->propertyCount();
}

int MiPropertyBag::propertyIndex(const QString &name) const
{
    return d->object->metaObject()->indexOfProperty(qPrintable(name));
}

QString MiPropertyBag::propertyName(int i) const
{
    return QString(d->object->metaObject()->property(i).name());
}

QString MiPropertyBag::propertyType(int i) const
{
    return d->object->metaObject()->property(i).typeName();
}

bool MiPropertyBag::isPropertyWritable(int i) const
{
    return d->object->metaObject()->property(i).isWritable();
}

QVariant MiPropertyBag::propertyValue(int i) const
{
    return d->object->metaObject()->property(i).read(this);
}

void MiPropertyBag::setPropertyValue(int i, const QVariant &value)
{
    const QMetaObject *metaObject = d->object->metaObject();
    bool ok = metaObject->property(i).write(this, value);
    if (!ok && value.isValid())
        metaObject->property(i).write(this, QVariant());
}
