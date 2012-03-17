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

#include "ac_gridsettings.h"

#include <ac_graphicsitem.h>
#include <ac_gridline.h>
#include <ac_score.h>

GridSettingsPrivate::GridSettingsPrivate(GridSettings *q)
    :   GraphicsParentPrivate(q)
    ,   snapToGrid(true)
    ,   timeGridLines(0)
    ,   pitchGridLines(0)
    ,   controlGridLines(0)
{
    mainGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
    mainGraphicsItems.insert(Ac::TimeLabelScene, new GraphicsItem);
    mainGraphicsItems.insert(Ac::PitchLabelScene, new GraphicsItem);
    mainGraphicsItems.insert(Ac::ControlLabelScene, new GraphicsItem);
    unitXGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
    unitXGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
    unitYGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
}

void GridSettingsPrivate::init()
{
    timeGridLines = new ObjectTList<TimeGridLine>(q_ptr);
    pitchGridLines = new ObjectTList<PitchGridLine>(q_ptr);
    controlGridLines = new ObjectTList<ControlGridLine>(q_ptr);
}

GridSettingsPrivate::~GridSettingsPrivate()
{
    qDeleteAll(controlGridLines);
    qDeleteAll(pitchGridLines);
    qDeleteAll(timeGridLines);
    delete controlGridLines;
    delete pitchGridLines;
    delete timeGridLines;
}

GraphicsParentPrivate *GridSettingsPrivate::graphicsParent() const
{
    Q_Q(const GridSettings);
    Score *score = q->score();
    return score ? score->d_func() : 0;
}

GridSettings::GridSettings(QObject *parent)
    :   GraphicsParent(*(new GridSettingsPrivate(this)), parent)
{
    Q_D(GridSettings);
    d->init();
    setName("GridSettings");
}

Score *GridSettings::score() const
{
    return object_cast<Score>(QObject::parent());
}

bool GridSettings::snapToGrid() const
{
    Q_D(const GridSettings);
    return d->snapToGrid;
}

void GridSettings::setSnapToGrid(bool snap)
{
    Q_D(GridSettings);
    if (d->snapToGrid == snap)
        return;
    d->beginChangeData();
    d->snapToGrid = snap;
    d->endChangeData();
}

ObjectTList<TimeGridLine> *GridSettings::timeGridLines() const
{
    Q_D(const GridSettings);
    return d->timeGridLines;
}

ObjectTList<PitchGridLine> *GridSettings::pitchGridLines() const
{
    Q_D(const GridSettings);
    return d->pitchGridLines;
}

ObjectTList<ControlGridLine> *GridSettings::controlGridLines() const
{
    Q_D(const GridSettings);
    return d->controlGridLines;
}

void GridSettings::clear()
{
    Q_D(GridSettings);
    d->controlGridLines->clear();
    d->pitchGridLines->clear();
    d->timeGridLines->clear();
    d->snapToGrid = true;
}

int GridSettings::modelItemIndex(const IModelItem *item) const
{
    Q_D(const GridSettings);
    if (d->timeGridLines == item)
        return 0;
    if (d->pitchGridLines == item)
        return 1;
    if (d->controlGridLines == item)
        return 2;
    return Object::modelItemIndex(item);
}

IModelItem *GridSettings::modelItemAt(int i) const
{
    switch (i) {
    case 0:
        return timeGridLines();
    case 1:
        return pitchGridLines();
    case 2:
        return controlGridLines();
    default:
        return 0;
    }
}

IModelItem *GridSettings::findModelItemList(int type) const
{
    switch (type) {
    case Ac::TimeGridLineItem:
        return timeGridLines();
    case Ac::PitchGridLineItem:
        return pitchGridLines();
    case Ac::ControlGridLineItem:
        return controlGridLines();
    default:
        return 0;
    }
}

QVariant GridSettings::data(int role) const
{
    switch (role) {
    case Ac::SnapRole:
        return snapToGrid();
    default:
        return GraphicsParent::data(role);
    }
}

bool GridSettings::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::SnapRole:
        setSnapToGrid(value.toBool());
        return true;
    default:
        return GraphicsParent::setData(value, role);
    }
}
