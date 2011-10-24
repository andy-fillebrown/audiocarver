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

#ifndef AC_PROXYMODEL_H
#define AC_PROXYMODEL_H

#include <ac_global.h>

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
        int mappedRole = -1;
        int column = index.column();
        const RoleMapList &maps = roleMaps();
        if (0 <= column && column < maps.count())
            mappedRole = maps.at(column).value(role, -1);
        if (mappedRole == -1)
            return QVariant();
        return QSortFilterProxyModel::data(index, mappedRole);
    }

private:
    RolesToColumnsProxyModelPrivate *d;
};

#endif // AC_PROXYMODEL_H
