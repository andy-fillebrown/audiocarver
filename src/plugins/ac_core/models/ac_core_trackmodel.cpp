/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_core_trackmodel.h"
#include "ac_core_model.h"
#include "ac_core_namespace.h"
#include <QMimeData>
#include <QStringList>

using namespace Mi;
using namespace Qt;

static const char mimeType[] = "AudioCarver track numbers";

namespace Ac {
namespace Core {

static TrackModel *instance = 0;

TrackModel *TrackModel::instance()
{
    return Ac::Core::instance;
}

TrackModel::TrackModel(QObject *parent)
    :   RolesToColumnsProxyModel(parent)
{
    RoleMapList role_maps;
    for (int i = 0;  i < 3;  ++i)
        role_maps.append(RoleMap());
    role_maps[0].insert(DisplayRole, ColorRole);
    role_maps[0].insert(EditRole, ColorRole);
    role_maps[1].insert(DisplayRole, NameRole);
    role_maps[1].insert(EditRole, NameRole);
    role_maps[2].insert(DisplayRole, VisibilityRole);
    setRoleMaps(role_maps);
    setSourceModel(qobject_cast<QAbstractItemModel*>(parent));
    Ac::Core::instance = this;
}

bool TrackModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    int type = index.data(ItemTypeRole).toInt();
    if (TrackItem == type)
        return true;
    return ListItem == type && TrackItem == index.data(ListTypeRole).toInt();
}

QStringList TrackModel::mimeTypes() const
{
    return RolesToColumnsProxyModel::mimeTypes() << mimeType;
}

QMimeData *TrackModel::mimeData(const QModelIndexList &indexes) const
{
    QList<int> rows;
    foreach (const QModelIndex &index, indexes)
        if (!rows.contains(index.row()))
            rows.append(index.row());
    qSort(rows);
    QByteArray mime_stream_data;
    QDataStream mime_stream(&mime_stream_data, QIODevice::WriteOnly);
    for (int i = rows.count() - 1;  0 <= i;  --i)
        mime_stream << rows.at(i);
    QMimeData *mime_data = RolesToColumnsProxyModel::mimeData(indexes);
    mime_data->setData(mimeType, mime_stream_data);
    return mime_data;
}

}
}
