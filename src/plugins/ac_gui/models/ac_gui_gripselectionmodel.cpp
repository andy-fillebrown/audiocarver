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

#include "ac_gui_gripselectionmodel.h"
#include "ac_gui_namespace.h"
#include <igraphicsgrip.h>
#include <igraphicsdelegate.h>
#include <igraphicsitem.h>
#include <QTimer>
#include <QPointF>

using namespace Ac;
using namespace Qt;

int gripType(IGraphicsGrip *grip)
{
    IGraphicsItem *sub_entity = query<IGraphicsItem>(grip)->parent();
    if (!sub_entity)
        return -1;
    return sub_entity->sceneType();
}

QString gripTypeName(IGraphicsGrip *grip)
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
    QList<IGraphicsGrip*> grips;
    QTimer updateTimer;

    GripSelectionModelPrivate(GripSelectionModel *q)
        :   q(q)
    {
        updateTimer.setSingleShot(true);
    }
};

static GripSelectionModel *instance = 0;

GripSelectionModel *GripSelectionModel::instance()
{
    return ::instance;
}

GripSelectionModel::GripSelectionModel(QObject *parent)
    :   QAbstractTableModel(parent)
    ,   d(new GripSelectionModelPrivate(this))
{
    ::instance = this;
    connect(&d->updateTimer, SIGNAL(timeout()), SLOT(delayedUpdate()));
}

GripSelectionModel::~GripSelectionModel()
{
    ::instance = 0;
    delete d;
}

int GripSelectionModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

int GripSelectionModel::rowCount(const QModelIndex &parent) const
{
    return d->grips.count();
}

Qt::ItemFlags GripSelectionModel::flags(const QModelIndex &index) const
{
    ItemFlags flags = ItemIsEnabled;
    if (2 < index.column() && index.column() < 4)
        flags |= ItemIsEditable;
    else if ((2 == index.column() || 4 == index.column()))
        flags |= ItemIsEditable;
    return flags;
}

QVariant GripSelectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (DisplayRole != role
            || Horizontal != orientation
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
    if (role != DisplayRole && role != EditRole)
        return QVariant();

    IGraphicsGrip *grip = d->grips.at(index.row());
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
        if (BezierCurve == grip->curveType())
            return true;
        else
            return false;
    default:
        return QVariant();
    }
}

bool GripSelectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != DisplayRole && role != EditRole)
        return false;
    IGraphicsGrip *grip = d->grips.at(index.row());
    if (!grip)
        return false;
    IGraphicsItem *parent = query<IGraphicsItem>(grip)->parent();
    IGraphicsDelegate *delegate = query<IGraphicsDelegate>(parent);
    switch (index.column()) {
    case 2:
        grip->update(PositionRole, QPointF(value.toReal(), grip->position().y()));
        qSort(d->grips.begin(), d->grips.end(), IGraphicsGrip::lessThan);
        delegate->updateModel();
        break;
    case 3:
        grip->update(PositionRole, QPointF(grip->position().x(), value.toReal()));
        qSort(d->grips.begin(), d->grips.end(), IGraphicsGrip::lessThan);
        delegate->updateModel();
        break;
    case 4:
        grip->update(CurveTypeRole, value.toInt());
        delegate->updateModel();
        break;
    default:
        return false;
    }
    return true;
}

void GripSelectionModel::delayedUpdate()
{
    if (d->grips.isEmpty())
        emit gripsDeselected();
    else
        emit gripsSelected();
    emit layoutChanged();
}

void GripSelectionModel::appendGrip(IGraphicsGrip *grip)
{
    if (d->grips.contains(grip))
        return;
    d->grips.append(grip);
    qSort(d->grips.begin(), d->grips.end(), IGraphicsGrip::lessThan);
    update();
}

void GripSelectionModel::removeGrip(IGraphicsGrip *grip)
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
    d->updateTimer.start();
}
