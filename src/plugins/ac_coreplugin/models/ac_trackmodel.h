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

#ifndef AC_TRACKMODEL_H
#define AC_TRACKMODEL_H

#include <ac_namespace.h>
#include <ac_proxymodel.h>

class AC_CORE_EXPORT TrackModel : public RolesToColumnsProxyModel
{
    Q_OBJECT

public:
    TrackModel(QObject *parent = 0)
        :   RolesToColumnsProxyModel(parent)
    {
        RoleMapList roleMaps;
        for (int i = 0;  i < 4;  ++i)
            roleMaps.append(RoleMap());
        roleMaps[0].insert(Qt::BackgroundRole, Ac::ColorRole);
        roleMaps[1].insert(Qt::DisplayRole, Ac::NameRole);
        roleMaps[2].insert(Qt::DisplayRole, Ac::VisibilityRole);
        roleMaps[3].insert(Qt::DisplayRole, Ac::RecordingRole);
        setRoleMaps(roleMaps);
        setSourceModel(qobject_cast<QAbstractItemModel*>(parent));
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
    {
        QAbstractItemModel *m = sourceModel();
        Q_ASSERT(m);
        if (!m)
            return false;
        QModelIndex index = m->index(sourceRow, 0, sourceParent);
        Ac::ItemType type = Ac::ItemType(index.data(Ac::ItemTypeRole).toInt());
        if (Ac::TrackItem == type)
            return true;
        if (Ac::ListItem == type) {
            Ac::ItemType listType = Ac::ItemType(index.data(Ac::ListTypeRole).toInt());
            if (Ac::TrackItem == listType)
                return true;
        }
        return false;
    }
};

#endif // AC_MODEL_H