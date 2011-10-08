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

#include "ac_gridsettings.h"

#include <ac_graphicsitem.h>
#include <ac_gridline.h>
#include <ac_score.h>

GridSettingsPrivate::GridSettingsPrivate(GridSettings *q)
    :   GraphicsParentPrivate(q)
    ,   timeGridLines(0)
    ,   pitchGridLines(0)
    ,   controlGridLines(0)
{
    mainGraphicsItems.insert(Ac::TimeLabelScene, new GraphicsItem);
    mainGraphicsItems.insert(Ac::PitchLabelScene, new GraphicsItem);
    mainGraphicsItems.insert(Ac::ControlLabelScene, new GraphicsItem);
    unitXGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
    unitXGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
    unitYGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
    unitYGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
}

void GridSettingsPrivate::init()
{
    timeGridLines = new ObjectList<TimeGridLine>(q_ptr);
    pitchGridLines = new ObjectList<PitchGridLine>(q_ptr);
    controlGridLines = new ObjectList<ControlGridLine>(q_ptr);
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
    setObjectName("GridSettings");
}

Score *GridSettings::score() const
{
    return qobject_cast<Score*>(QObject::parent());
}

ObjectList<TimeGridLine> *GridSettings::timeGridLines() const
{
    Q_D(const GridSettings);
    return d->timeGridLines;
}

ObjectList<PitchGridLine> *GridSettings::pitchGridLines() const
{
    Q_D(const GridSettings);
    return d->pitchGridLines;
}

ObjectList<ControlGridLine> *GridSettings::controlGridLines() const
{
    Q_D(const GridSettings);
    return d->controlGridLines;
}

int GridSettings::modelItemIndex(IModelItem *item) const
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

IModelItem *GridSettings::findModelItemList(Ac::ItemType type) const
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