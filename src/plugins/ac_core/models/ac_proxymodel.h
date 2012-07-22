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

#ifndef AC_PROXYMODEL_H
#define AC_PROXYMODEL_H

#include <ac_core_global.h>

#include <QSortFilterProxyModel>

typedef QMap<int, int> RoleMap;
typedef QList<RoleMap> RoleMapList;

class RolesToColumnsProxyModelPrivate;
class AC_CORE_EXPORT RolesToColumnsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit RolesToColumnsProxyModel(QObject *parent = 0);
    ~RolesToColumnsProxyModel();

    const RoleMapList &roleMaps() const;
    void setRoleMaps(const RoleMapList &roleMaps);

    int mappedRole(const QModelIndex &index, int proxyRole) const
    {
        int role = -1;
        int column = index.column();
        const RoleMapList &maps = roleMaps();
        if (0 <= column && column < maps.count())
            role = maps.at(column).value(proxyRole, -1);
        return role;
    }

    // QSortFilterProxyModel

    bool filterAcceptsColumn(int, const QModelIndex &) const
    {
        return true;
    }

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const
    {
        return QSortFilterProxyModel::mapToSource(createIndex(proxyIndex.row(), 0, proxyIndex.internalPointer()));
    }

    void setSourceModel(QAbstractItemModel *sourceModel);

    // QAbstractItemModel

    int columnCount(const QModelIndex &) const
    {
        return roleMaps().count();
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        int mapped_role = mappedRole(index, role);
        if (mapped_role == -1)
            return QVariant();
        return QSortFilterProxyModel::data(index, mapped_role);
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role)
    {
        int mapped_role = mappedRole(index, role);
        if (mapped_role == -1)
            return false;
        return QSortFilterProxyModel::setData(index, value, mapped_role);
    }

private:
    RolesToColumnsProxyModelPrivate *d;
};

#endif // AC_PROXYMODEL_H
