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

#include "ac_gripselectionmodel.h"

#include <ac_ientityitem.h>
#include <ac_igripitem.h>

#include <ac_ientity.h>
#include <ac_namespace.h>

#include <QPointF>

int gripType(IGripItem *grip)
{
    IEntityItem *entity_item = grip->parentEntityItem();
    IEntity *entity = entity_item->entity();
    ISubEntity *sub_entity = query<ISubEntity>(entity);
    if (!sub_entity)
        return -1;
    return sub_entity->sceneType();
}

QString gripTypeName(IGripItem *grip)
{
    switch (gripType(grip)) {
    case Ac::PitchScene:
        return "Pitch Grip";
    case Ac::ControlScene:
        return "Control Grip";
    default:
        return "";
    }
}

class GripSelectionModelPrivate
{
public:
    GripSelectionModel *q;
    QList<IGripItem*> grips;

    GripSelectionModelPrivate(GripSelectionModel *q)
        :   q(q)
    {}
};

static GripSelectionModel *instance = 0;

GripSelectionModel::GripSelectionModel(QObject *parent)
    :   QAbstractTableModel(parent)
    ,   d(new GripSelectionModelPrivate(this))
{
    ::instance = this;
}

GripSelectionModel::~GripSelectionModel()
{
    ::instance = 0;
    delete d;
}

GripSelectionModel *GripSelectionModel::instance()
{
    return ::instance;
}

int GripSelectionModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

int GripSelectionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->grips.count();
}

Qt::ItemFlags GripSelectionModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled;
    if (0 < index.column())
        flags |= Qt::ItemIsEditable;
    return flags;
}

QVariant GripSelectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole != role
            || Qt::Horizontal != orientation
            || section < 0 || 3 < section)
        return QVariant();

    switch (section) {
    case 0:
        return "Grip Type";
    case 1:
        return "Time";
    case 2:
        return "Value";
    case 3:
        return "Curve Type";
    default:
        return "";
    }
}

QVariant GripSelectionModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole
            && role != Qt::EditRole)
        return QVariant();

    IGripItem *grip_item = d->grips.at(index.row());
    if (!grip_item)
        return QVariant();

    switch (index.column()) {
    case 0:
        return gripTypeName(grip_item);
    case 1:
        return grip_item->position().x();
    case 2:
        return grip_item->position().y();
    case 3:
        return "n/a";
    default:
        return QVariant();
    }
}

bool GripSelectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index);
    Q_UNUSED(value);
    Q_UNUSED(role);
    return true;
}

void GripSelectionModel::appendGrip(IGripItem *grip)
{
    if (d->grips.contains(grip))
        return;
    d->grips.append(grip);
    qSort(d->grips.begin(), d->grips.end(), IGripItem::lessThan);
    update();
}

void GripSelectionModel::removeGrip(IGripItem *grip)
{
    d->grips.removeOne(grip);
    update();
}

void GripSelectionModel::update()
{
    if (d->grips.count() == 1)
        emit gripsSelected();
    else if (d->grips.isEmpty())
        emit gripsDeselected();
    emit layoutChanged();
}
