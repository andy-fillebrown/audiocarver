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

#ifndef AC_CORE_TRACKMODEL_H
#define AC_CORE_TRACKMODEL_H

#include "ac_core_rolestocolumnsproxymodel.h"

namespace Core {

class AC_CORE_EXPORT TrackModel : public RolesToColumnsProxyModel
{
    Q_OBJECT

public:
    TrackModel(QObject *parent = 0);

    static TrackModel *instance();

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        Qt::ItemFlags extraFlags = Qt::ItemIsSelectable;
        if (1 == index.column())
            extraFlags |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled;
        return  extraFlags | RolesToColumnsProxyModel::flags(index);
    }

    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
};

}

#endif
