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

#ifndef MI_CORENAMESPACE_H
#define MI_CORENAMESPACE_H

#include <mi_coreglobal.h>

#include <qnamespace.h>

namespace I {

enum MiCoreInterfaces {
    IAggregate,
    IAggregator,
    IFactory,
    IModel,
    IModelData,
    IModelDataWatcher,
    IModelItem,
    IModelItemWatcher,
    IModelList,
    IObject,
    IOrphanage,
    MiCoreInterfaceCount
};

} // namespace I

namespace Mi {

enum ItemType {
    UnknownItem,
    ListItem,
    ItemTypeCount
};

MI_CORE_EXPORT void appendItemType(int itemType, const QString itemTypeString);
MI_CORE_EXPORT QString itemTypeString(int itemType);
MI_CORE_EXPORT int itemType(const QString &itemTypeString);

enum ItemDataRole {
    InvalidRole = Qt::UserRole,
    ItemTypeRole,
    ListTypeRole,
    RoleTypeRole,
    NameRole,
    ItemDataRoleCount
};

MI_CORE_EXPORT void appendItemDataRole(int itemDataRole, const QString itemDataRoleString);
MI_CORE_EXPORT QString itemDataRoleString(int itemDataRole);
MI_CORE_EXPORT int itemDataRole(const QString &itemDataRoleString);

enum NotificationFlags {
    NotifyModel = 0x1,
    NotifyParent = 0x2,
    NotifyModelAndParent = 0x3
};

} // namespace Mi

#endif // MI_CORENAMESPACE_H

// TODO:  Move namespace I to separate header.
