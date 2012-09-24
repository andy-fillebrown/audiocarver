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

#include <mi_namespace.h>

static const QMap<int, QString> &itemDataRoleMap()
{
    static QMap<int, QString> map;
    if (map.isEmpty()) {
        map.insert(Mi::ItemTypeRole, "type");
        map.insert(Mi::ListTypeRole, "listType");
        map.insert(Mi::NameRole, "name");
    }
    return map;
}

namespace Mi {

QString itemDataRoleString(int itemDataRole)
{
    const QMap<int, QString> &map = itemDataRoleMap();
    if (map.contains(itemDataRole))
        return map.value(itemDataRole);
    return QString();
}

int itemDataRole(const QString &itemDataRoleString)
{
    const QMap<int, QString> &map = itemDataRoleMap();
    QList<QString> values = map.values();
    if (values.contains(itemDataRoleString))
        return map.keys().at(values.indexOf(itemDataRoleString));
    return -1;
}

} // namespace Mi
