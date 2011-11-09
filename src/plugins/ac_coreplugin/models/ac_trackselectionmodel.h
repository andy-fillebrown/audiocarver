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

#ifndef AC_TRACKSELECTIONMODEL_H
#define AC_TRACKSELECTIONMODEL_H

#include <ac_global.h>
#include <ac_namespace.h>

#include <QItemSelectionModel>

class IModelItem;

class AC_CORE_EXPORT TrackSelectionModel : public QItemSelectionModel
{
    Q_OBJECT

public:
    TrackSelectionModel(QAbstractItemModel *model);

    static TrackSelectionModel *instance();

    QModelIndexList selectedTrackIndexes() const;
    QList<IModelItem*> selectedTracks() const;
};

#endif // AC_TRACKSELECTIONMODEL_H
