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

#include "ac_trackmodel.h"

#include <ac_model.h>

#include <mi_idatabase.h>

#include <QMimeData>
#include <QStringList>

static const char mimeType[] = "AudioCarver track numbers";

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

bool TrackModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    if (Qt::MoveAction != action)
        return true;
    const QStringList formats = data->formats();
    if (!formats.contains(mimeType))
        return false;
    IModel *model = IDatabase::instance()->model();
    QByteArray b = data->data(mimeType);
    QDataStream stream(&b, QIODevice::ReadOnly);
    int fromRow = -1;
    QList<int> fromRows;
    while (!stream.atEnd()) {
        stream >> fromRow;
        fromRows.append(fromRow);
    }
    int toRow = row;
    if (fromRows.contains(toRow))
        return false;
    const QModelIndex trackListIndex = model->listIndex(Ac::TrackItem);
    QList<IModelItem*> items;
    foreach (int row, fromRows) {
        items.append(model->takeItem(row, trackListIndex));
        if (row < toRow)
            --toRow;
    }
    foreach (IModelItem *item, items)
        model->insertItem(item, toRow, trackListIndex);
    return true;
}
