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

#include "ac_gridline.h"

#include <ac_gridsettings.h>

#include <QGraphicsItem>

GridLinePrivate::GridLinePrivate(GridLine *q)
    :   GraphicsObjectPrivate(q)
    ,   location(0.0f)
    ,   priority(0)
    ,   color(Qt::lightGray)
{}

GraphicsParentPrivate *GridLinePrivate::graphicsParent() const
{
    Q_Q(const GridLine);
    GridSettings *gridSettings = q->gridSettings();
    return gridSettings ? gridSettings->d_func() : 0;
}

GridLine::GridLine(GridLinePrivate &dd, QObject *parent)
    :   GraphicsObject(dd, parent)
{}

qreal GridLine::location() const
{
    Q_D(const GridLine);
    return d->location;
}

void GridLine::setLocation(qreal location)
{
    Q_D(GridLine);
    if (location < 0.0f)
        location = 0.0f;
    if (d->location == location)
        return;
    d->beginChangeData();
    d->location = location;
    d->endChangeData();
}

const QString &GridLine::label() const
{
    Q_D(const GridLine);
    return d->label;
}

void GridLine::setLabel(const QString &label)
{
    Q_D(GridLine);
    if (d->label == label)
        return;
    d->beginChangeData();
    d->label = label;
    d->endChangeData();
}

int GridLine::priority() const
{
    Q_D(const GridLine);
    return d->priority;
}

void GridLine::setPriority(int priority)
{
    Q_D(GridLine);
    if (d->priority == priority)
        return;
    d->beginChangeData();
    d->priority = priority;
    d->endChangeData();
}

const QColor &GridLine::color() const
{
    Q_D(const GridLine);
    return d->color;
}

void GridLine::setColor(const QColor &color)
{
    Q_D(GridLine);
    if (d->color == color)
        return;
    d->beginChangeData();
    d->color = color;
    d->endChangeData();
}

GridSettings *GridLine::gridSettings() const
{
    QObject *parent = QObject::parent();
    return parent ? qobject_cast<GridSettings*>(parent->parent()) : 0;
}

TimeGridLine::TimeGridLine(QObject *parent)
    :   GridLine(*(new TimeGridLinePrivate(this)), parent)
{
    setObjectName("TimeGridLine");
}

PitchGridLine::PitchGridLine(QObject *parent)
    :   GridLine(*(new PitchGridLinePrivate(this)), parent)
{
    setObjectName("PitchGridLine");
}

ControlGridLine::ControlGridLine(QObject *parent)
    :   GridLine(*(new ControlGridLinePrivate(this)), parent)
{
    setObjectName("ControlGridLine");
}
