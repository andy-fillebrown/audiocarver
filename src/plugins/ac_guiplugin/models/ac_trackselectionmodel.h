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

#ifndef AC_TRACKSELECTIONMODEL_H
#define AC_TRACKSELECTIONMODEL_H

#include <ac_global.h>
#include <ac_namespace.h>

#include <mi_itemselectionmodel.h>

class AC_CORE_EXPORT TrackSelectionModel : public ItemSelectionModel
{
    Q_OBJECT

public:
    TrackSelectionModel(QAbstractItemModel *model);

    static TrackSelectionModel *instance();

    QModelIndexList selectedTrackIndexes() const;
    virtual QList<IModelItem*> selectedItems() const;
};

#endif // AC_TRACKSELECTIONMODEL_H