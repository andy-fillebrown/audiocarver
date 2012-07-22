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

#include "ac_noteselectionmodel.h"

#include <mi_idatabase.h>
#include <mi_core_qmodel.h>

#include <ac_trackselectionmodel.h>

static NoteSelectionModel *instance = 0;

NoteSelectionModel::NoteSelectionModel(QAbstractItemModel *model)
    :   ItemSelectionModel(model)
{
    ::instance = this;
}

NoteSelectionModel *NoteSelectionModel::instance()
{
//    if (!::instance)
//        new NoteSelectionModel(query<IQModel>(IDatabase::instance()));
    return ::instance;
}

void NoteSelectionModel::select(const QItemSelection &selection, SelectionFlags command)
{
    if (Select & command
            && !selection.isEmpty())
        TrackSelectionModel::instance()->clear();

    QItemSelection ss;
    const QModelIndexList indexes = selection.indexes();
    foreach (const QModelIndex &index, indexes)
        if (Ac::NoteItem == index.data(Mi::ItemTypeRole).toInt()
                && index.data(Ac::VisibilityRole).toBool())
            ss.select(index, index);

    QItemSelectionModel::select(ss, command);
}
