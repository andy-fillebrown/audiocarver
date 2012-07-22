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

#include <ac_igrip.h>
#include <ac_isubentity.h>

#include <QPointF>

using namespace Ac;

bool isCurveGrip(IGrip *grip)
{
    ISubEntity *sub_entity = grip->entity();
    if (!sub_entity)
        return false;
    return sub_entity->isCurve();
}

int gripType(IGrip *grip)
{
    ISubEntity *sub_entity = grip->entity();
    if (!sub_entity)
        return -1;
    return sub_entity->sceneType();
}

QString gripTypeName(IGrip *grip)
{
    switch (gripType(grip)) {
    case PitchScene:
        return "pitch";
    case ControlScene:
        return "control";
    default:
        return "";
    }
}

class GripSelectionModelPrivate
{
public:
    GripSelectionModel *q;
    QList<IGrip*> grips;

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
    return 5;
}

int GripSelectionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->grips.count();
}

Qt::ItemFlags GripSelectionModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled;
    if (2 < index.column() && index.column() < 4)
        flags |= Qt::ItemIsEditable;
    else if ((2 == index.column() || 4 == index.column())
            && isCurveGrip(d->grips.at(index.row())))
        flags |= Qt::ItemIsEditable;
    return flags;
}

QVariant GripSelectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole != role
            || Qt::Horizontal != orientation
            || section < 1 || 4 < section)
        return QVariant();

    switch (section) {
    case 1:
        return "Type";
    case 2:
        return "Time";
    case 3:
        return "Value";
    case 4:
        return "Curved";
    default:
        return "";
    }
}

QVariant GripSelectionModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole
            && role != Qt::EditRole)
        return QVariant();

    IGrip *grip = d->grips.at(index.row());
    if (!grip)
        return QVariant();

    switch (index.column()) {
    case 1:
        return gripTypeName(grip);
    case 2:
        return grip->position().x();
    case 3:
        return grip->position().y();
    case 4:
        if (!isCurveGrip(grip))
            return "n/a";
        if (Ac::BezierCurve == grip->curveType())
            return true;
        else
            return false;
    default:
        return QVariant();
    }
}

bool GripSelectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::DisplayRole
            && role != Qt::EditRole)
        return false;
    IGrip *grip = d->grips.at(index.row());
    if (!grip)
        return false;
    switch (index.column()) {
    case 2:
        grip->setPosition(QPointF(value.toReal(), grip->position().y()));
        qSort(d->grips.begin(), d->grips.end(), IGrip::lessThan);
        grip->entity()->finishUpdatingPoints();
        break;
    case 3:
        grip->setPosition(QPointF(grip->position().x(), value.toReal()));
        qSort(d->grips.begin(), d->grips.end(), IGrip::lessThan);
        grip->entity()->finishUpdatingPoints();
        break;
    case 4:
        grip->setCurveType(value.toInt());
        grip->entity()->updateCurveTypes();
        break;
    default:
        return false;
    }
    return true;
}

void GripSelectionModel::appendGrip(IGrip *grip)
{
    if (d->grips.contains(grip))
        return;
    d->grips.append(grip);
    qSort(d->grips.begin(), d->grips.end(), IGrip::lessThan);
    update();
}

void GripSelectionModel::removeGrip(IGrip *grip)
{
    // Emit gripDeselected, even if it's not selected, so the graphics views
    // get the signal and remove the grip from thier hovered grip lists.
    emit gripDeselected(grip);
    if (!d->grips.contains(grip))
        return;
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
