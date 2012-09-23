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

#include "ac_trackmodel.h"

#include <ac_model.h>

#include <mi_idatabase.h>

#include <QMimeData>
#include <QStringList>

static const char mimeType[] = "AudioCarver track numbers";

static TrackModel *instance = 0;

TrackModel::TrackModel(QObject *parent)
    :   RolesToColumnsProxyModel(parent)
{
    RoleMapList roleMaps;
    for (int i = 0;  i < 4;  ++i)
        roleMaps.append(RoleMap());
    roleMaps[0].insert(Qt::DisplayRole, Ac::ColorRole);
    roleMaps[0].insert(Qt::EditRole, Ac::ColorRole);
    roleMaps[1].insert(Qt::DisplayRole, Mi::NameRole);
    roleMaps[1].insert(Qt::EditRole, Mi::NameRole);
    roleMaps[2].insert(Qt::DisplayRole, Ac::VisibilityRole);
    roleMaps[3].insert(Qt::DisplayRole, Ac::RecordingRole);
    setRoleMaps(roleMaps);

    setSourceModel(object_cast<QAbstractItemModel>(parent));

    ::instance = this;
}

TrackModel *TrackModel::instance()
{
    if (!::instance)
        new TrackModel(IModel::instance());
    return ::instance;
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
    QByteArray b;
    QDataStream stream(&b, QIODevice::WriteOnly);
    for (int i = rows.count() - 1;  0 <= i;  --i)
        stream << rows.at(i);
    QMimeData *mimeData = RolesToColumnsProxyModel::mimeData(indexes);
    mimeData->setData(mimeType, b);
    return mimeData;
}
