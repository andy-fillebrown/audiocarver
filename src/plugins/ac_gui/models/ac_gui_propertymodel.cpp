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

#include "ac_gui_propertymodel.h"

using namespace Qt;

int PropertyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

Qt::ItemFlags PropertyModel::flags(const QModelIndex &index) const
{
    const ItemFlags default_flags = ItemIsEnabled;
    if (1 == index.column())
        return default_flags | ItemIsEditable;
    return default_flags;
}

QVariant PropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (DisplayRole != role
            || Horizontal != orientation
            || section < 0 || 1 < section)
        return QVariant();

    if (0 == section)
        return "Property";
    return "Value";
}
