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

#include "mi_root.h"
#include <QMetaType>

MiRoot::MiRoot(QObject *parent)
    :   MiObject(parent)
{}

void MiRoot::clear()
{}

QString &MiRoot::normalizeClassName(QString &className) const
{
    return className;
}

QString MiRoot::getUniqueId(MiObject *object, const QString &idHint) const
{
    QString actualId = idHint;
    if (actualId.isEmpty())
        actualId = object->className() + ".1";
    bool idIsUsed = false;
    QList<MiObject*> children = findChildren<MiObject*>();
    foreach (MiObject *object, children) {
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
    foreach (MiObject *object, children) {
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

QString MiRoot::variantToString(const QVariant &variant) const
{
    int type = variant.type();
    if (type == QVariant::Double || type == QMetaType::Float) {
        QString s = QString("%1").arg(variant.toDouble(), 0, 'f', 6);
        while (s.contains(".") && s.endsWith("0"))
            s.chop(1);
        if (s.endsWith("."))
            s.chop(1);
        return s;
    }
    if (variant.type() == QVariant::Bool)
        return variant.toBool() ? "1" : "0";
    return variant.toString();
}

QVariant MiRoot::stringToVariant(const QString &string, const QString &type) const
{
    if (type == "Bool")
        return QVariant(string == "1");
    return QVariant(string);
}
