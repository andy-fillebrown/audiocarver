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

static const char mimeFormat[] = "application/x-qabstractitemmodeldatalist";

bool TrackModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    if (Qt::IgnoreAction == action)
        return true;
    const QStringList formats = data->formats();
    if (!formats.contains(mimeFormat))
        return false;
    QByteArray b = data->data(mimeFormat);
    QDataStream stream(&b, QIODevice::ReadOnly);
    int fromRow = -1;
    stream >> fromRow;
    const int toRow = parent.row();
    if (fromRow == toRow)
        return true;
    Model *model = qobject_cast<Model*>(IDatabase::instance()->model());
    if (!model)
        return false;
    const QModelIndex trackList = model->trackListIndex();
    IModelItem *item = model->takeItem(fromRow, trackList);
    model->insertItem(item, toRow, trackList);
    return true;
}
