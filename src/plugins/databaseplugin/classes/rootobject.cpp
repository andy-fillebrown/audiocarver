/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "rootobject.h"

using namespace Database;

RootObject::RootObject(QObject *parent)
    :   Object(parent)
{
}

RootObject::~RootObject()
{
}

QString &RootObject::normalizeClassName(QString &className) const
{
    return className;
}

QString RootObject::getUniqueId(Object *object, const QString &idHint) const
{
    QString actualId = idHint;
    if (actualId.isEmpty())
        actualId = object->className() + ".1";

    bool idIsUsed = false;
    QList<Object*> children = findChildren<Object*>();
    foreach (Object *object, children)
    {
        Q_ASSERT(object);

        if (object->id() == actualId) {
            idIsUsed = true;
            break;
        }
    }

    if (!idIsUsed)
        return actualId;

    int lastIndexOfDot = actualId.lastIndexOf(".");
    if (lastIndexOfDot != -1)
        actualId = actualId.left(lastIndexOfDot);

    int maxSuffix = 0;

    foreach (Object *object, children) {
        Q_ASSERT(object);

        QString id = object->id();
        if (id.startsWith(actualId)) {
            int lastIndexOfDot = id.lastIndexOf(".");
            if (lastIndexOfDot == -1)
                continue;

            QString preDotName = id.left(lastIndexOfDot);
            if (actualId.startsWith(preDotName)) {
                QString suffix = id.mid(lastIndexOfDot + 1);
                maxSuffix = qMax(maxSuffix, suffix.toInt());
            }
        }
    }

    return actualId += QString(".%1").arg(maxSuffix + 1);
}

Object *RootObject::createObject(const QString &className) const
{
    Q_UNUSED(className);
    return 0;
}
