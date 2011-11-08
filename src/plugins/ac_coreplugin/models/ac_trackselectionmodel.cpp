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

#include "ac_trackselectionmodel.h"

#include <ac_trackmodel.h>

#include <mi_imodel.h>

static TrackSelectionModel *instance = 0;

TrackSelectionModel::TrackSelectionModel(QAbstractItemModel *model)
    :   QItemSelectionModel(model)
{
    ::instance = this;
}

TrackSelectionModel *TrackSelectionModel::instance()
{
    if (!::instance)
        new TrackSelectionModel(TrackModel::instance());
    return ::instance;
}

QList<IModelItem*> TrackSelectionModel::selectedTracks() const
{
    QList<int> rows;

    TrackModel *trackModel = TrackModel::instance();
    const QModelIndexList indexes = selectedIndexes();
    foreach (const QModelIndex &index, indexes) {
        const QModelIndex sourceIndex = object_cast<QSortFilterProxyModel>(trackModel->sourceModel())->mapToSource(trackModel->mapToSource(index));
        if (!rows.contains(sourceIndex.row()))
            rows.append(sourceIndex.row());
    }

    QList<IModelItem*> tracks;

    IModel *model = IModel::instance();
    const QModelIndex trackListIndex = model->listIndex(Ac::TrackItem);
    const int n = rows.count();
    for (int i = 0;  i < n; ++i)
        tracks.append(model->itemFromIndex(model->index(rows.at(i), trackListIndex)));

    return tracks;
}
