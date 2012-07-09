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
    ICopyFiler,
    IDatabase,
    IFactory,
    IFileFiler,
    IModel,
    IModelData,
    IModelDataWatcher,
    IModelItem,
    IModelItemWatcher,
    IModelList,
    IObject,
    IOrphanage,
    IReader,
    IWriter,
    MiCoreInterfaceCount
};

} // namespace I

namespace Mi {

enum ItemType {
    UnknownItem,
    ListItem,
    CoreItemTypeCount
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

enum DataChangeType {
    TemporarayDataChange,
    PermanentDataChange
};

} // namespace Mi

#endif // MI_CORENAMESPACE_H
