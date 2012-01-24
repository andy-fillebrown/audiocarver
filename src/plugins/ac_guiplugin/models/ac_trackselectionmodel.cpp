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

#include "ac_trackselectionmodel.h"

#include <ac_noteselectionmodel.h>

#include <ac_trackmodel.h>

#include <mi_imodel.h>

static TrackSelectionModel *instance = 0;

TrackSelectionModel::TrackSelectionModel(QAbstractItemModel *model)
    :   ItemSelectionModel(model)
{
    ::instance = this;
}

TrackSelectionModel *TrackSelectionModel::instance()
{
    if (!::instance)
        new TrackSelectionModel(TrackModel::instance());
    return ::instance;
}

QModelIndexList TrackSelectionModel::selectedTrackIndexes() const
{
    QModelIndexList trackIndexes;
    QList<int> rows;

    TrackModel *trackModel = TrackModel::instance();
    const QModelIndexList indexes = selectedIndexes();
    foreach (const QModelIndex &index, indexes) {
        const QModelIndex sourceIndex = object_cast<QSortFilterProxyModel>(trackModel->sourceModel())->mapToSource(trackModel->mapToSource(index));
        if (!rows.contains(sourceIndex.row())) {
            trackIndexes.append(sourceIndex);
            rows.append(sourceIndex.row());
        }
    }

    return trackIndexes;
}

QList<IModelItem*> TrackSelectionModel::selectedItems() const
{
    QList<IModelItem*> items;

    IModel *model = IModel::instance();
    const QModelIndexList indexes = selectedTrackIndexes();

    const int n = indexes.count();
    for (int i = 0;  i < n; ++i)
        items.append(model->itemFromIndex(indexes.at(i)));

    return items;
}

void TrackSelectionModel::select(const QItemSelection &selection, SelectionFlags command)
{
    if (Select & command)
        NoteSelectionModel::instance()->clear();

    ItemSelectionModel::select(selection, command);
}
