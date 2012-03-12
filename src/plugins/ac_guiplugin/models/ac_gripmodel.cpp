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

#include "ac_gripmodel.h"

#include <ac_gripmanager.h>
#include <ac_igripitem.h>

#include <ac_namespace.h>

#include <QPointF>

int GripModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

int GripModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return GripManager::instance()->gripCount(sceneType());
}

Qt::ItemFlags GripModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariant GripModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole != role
            || Qt::Horizontal != orientation
            || section < 0 || 2 < section)
        return QVariant();

    switch (section) {
    case 0:
        return "Time";
    case 1:
        if (Ac::PitchScene == sceneType())
            return "Pitch";
        else
            return "Value";
    case 2:
        return "Curve";
    default:
        return "";
    }
}

QVariant GripModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole
            && role != Qt::EditRole)
        return QVariant();

    IGripItem *grip_item = GripManager::instance()->gripAt(sceneType(), index.row());
    if (!grip_item)
        return QVariant();

    switch (index.column()) {
    case 0:
        return grip_item->position().x();
    case 1:
        return grip_item->position().y();
    case 3:
        return "n/a";
    default:
        return QVariant();
    }
}

bool GripModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index);
    Q_UNUSED(value);
    Q_UNUSED(role);
    return true;
}

int PitchGripModel::sceneType() const
{
    return Ac::PitchScene;
}

int ControlGripModel::sceneType() const
{
    return Ac::ControlScene;
}
