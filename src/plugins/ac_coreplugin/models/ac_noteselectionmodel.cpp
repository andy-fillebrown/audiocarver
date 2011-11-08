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

#include "ac_noteselectionmodel.h"

#include <mi_imodel.h>

static NoteSelectionModel *instance = 0;

NoteSelectionModel::NoteSelectionModel(QAbstractItemModel *model)
    :   QItemSelectionModel(model)
{
    ::instance = this;
}

NoteSelectionModel *NoteSelectionModel::instance()
{
    if (!::instance)
        new NoteSelectionModel(IModel::instance());
    return ::instance;
}

void NoteSelectionModel::select(const QItemSelection &selection, SelectionFlags command)
{
    QItemSelection ss;
    const QModelIndexList indexes = selection.indexes();
    foreach (const QModelIndex &index, indexes)
        if (Ac::NoteItem == index.data(Mi::ItemTypeRole).toInt())
            ss.select(index, index);

    QItemSelectionModel::select(ss, command);
}

QList<IModelItem*> NoteSelectionModel::selectedNotes() const
{
    QList<IModelItem*> notes;

    IModel *model = IModel::instance();
    const QModelIndexList indexes = selectedIndexes();
    foreach (const QModelIndex &index, indexes)
        notes.append(model->itemFromIndex(index));

    return notes;
}
