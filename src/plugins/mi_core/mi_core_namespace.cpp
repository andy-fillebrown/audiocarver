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

#include "mi_core_namespace.h"

static QMap<int, QString> item_type_map;
static QMap<int, QString> item_data_role_map;

void appendItemType(int itemType, const QString itemTypeString)
{
    QMap<int, QString> &map = item_type_map;
    if (map.contains(itemType))
        return;
    map.insert(itemType, itemTypeString);
}

QString itemTypeString(int itemType)
{
    const QMap<int, QString> &map = item_type_map;
    if (map.contains(itemType))
        return map.value(itemType);
    return QString();
}

int itemType(const QString &itemTypeString)
{
    const QMap<int, QString> &map = item_type_map;
    QList<QString> values = map.values();
    if (values.contains(itemTypeString))
        return map.keys().at(values.indexOf(itemTypeString));
    return -1;
}

void appendItemDataRole(int itemDataRole, const QString itemDataRoleString)
{
    QMap<int, QString> &map = item_data_role_map;
    if (map.contains(itemDataRole))
        return;
    map.insert(itemDataRole, itemDataRoleString);
}

QString itemDataRoleString(int itemDataRole)
{
    const QMap<int, QString> &map = item_data_role_map;
    if (map.contains(itemDataRole))
        return map.value(itemDataRole);
    return QString();
}

int itemDataRole(const QString &itemDataRoleString)
{
    const QMap<int, QString> &map = item_data_role_map;
    QList<QString> values = map.values();
    if (values.contains(itemDataRoleString))
        return map.keys().at(values.indexOf(itemDataRoleString));
    return -1;
}
