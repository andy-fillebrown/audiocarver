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
    d->updateGraphicsItems();
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
    d->updateGraphicsItems();
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
    d->updateGraphicsItems();
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
    d->updateGraphicsItems();
    d->endChangeData();
}

GridSettings *GridLine::gridSettings() const
{
    QObject *parent = QObject::parent();
    return parent ? qobject_cast<GridSettings*>(parent->parent()) : 0;
}

class TimeGridLinePrivate : public GridLinePrivate
{
public:
    GraphicsTextItem *timeLabelItem;
    QGraphicsLineItem *pitchLineItem;
    QGraphicsLineItem *controlLineItem;

    TimeGridLinePrivate(TimeGridLine *q)
        :   GridLinePrivate(q)
        ,   timeLabelItem(new GraphicsTextItem)
        ,   pitchLineItem(new QGraphicsLineItem)
        ,   controlLineItem(new QGraphicsLineItem)
    {}

    void init()
    {
        updateGraphicsParent();
        updateGraphicsItems();
    }

    ~TimeGridLinePrivate()
    {
        delete controlLineItem;
        delete pitchLineItem;
        delete timeLabelItem;
    }

    void updateGraphicsParent()
    {
        GraphicsParentPrivate *parent = graphicsParent();
        if (parent) {
            timeLabelItem->setParentItem(parent->mainGraphicsItems[Ac::TimeLabelScene]);
            pitchLineItem->setParentItem(parent->unitYGraphicsItems[Ac::PitchScene]);
            controlLineItem->setParentItem(parent->mainGraphicsItems[Ac::ControlScene]);
        } else {
            timeLabelItem->setParentItem(0);
            pitchLineItem->setParentItem(0);
            controlLineItem->setParentItem(0);
        }
    }

    void updateGraphicsItems()
    {
        timeLabelItem->setPos(location, 0.0f);
        timeLabelItem->setText(label);
        timeLabelItem->setColor(Qt::black);
        QPen pen(color);
        pen.setCosmetic(true);
        pitchLineItem->setPen(pen);
        controlLineItem->setPen(pen);
        QLineF line(location, 0.0f, location, 1.0f);
        pitchLineItem->setLine(line);
        controlLineItem->setLine(line);
    }
};

TimeGridLine::TimeGridLine(QObject *parent)
    :   GridLine(*(new TimeGridLinePrivate(this)), parent)
{
    Q_D(TimeGridLine);
    d->init();
    setObjectName("TimeGridLine");
}

bool TimeGridLine::isVisible() const
{
    Q_D(const TimeGridLine);
    return d->pitchLineItem->isVisible();
}

void TimeGridLine::show()
{
    Q_D(TimeGridLine);
    d->timeLabelItem->show();
    d->pitchLineItem->show();
    d->controlLineItem->show();
}

void TimeGridLine::hide()
{
    Q_D(TimeGridLine);
    d->timeLabelItem->hide();
    d->pitchLineItem->hide();
    d->controlLineItem->hide();
}

class PitchGridLinePrivate : public GridLinePrivate
{
public:
    GraphicsTextItem *pitchLabelItem;
    QGraphicsLineItem *pitchLineItem;

    PitchGridLinePrivate(PitchGridLine *q)
        :   GridLinePrivate(q)
        ,   pitchLabelItem(new GraphicsTextItem)
        ,   pitchLineItem(new QGraphicsLineItem)
    {}

    void init()
    {
        updateGraphicsParent();
        updateGraphicsItems();
    }

    ~PitchGridLinePrivate()
    {
        delete pitchLineItem;
        delete pitchLabelItem;
    }

    void updateGraphicsParent()
    {
        GraphicsParentPrivate *parent = graphicsParent();
        if (parent) {
            pitchLabelItem->setParentItem(parent->mainGraphicsItems[Ac::PitchLabelScene]);
            pitchLineItem->setParentItem(parent->unitXGraphicsItems[Ac::PitchScene]);
        } else {
            pitchLabelItem->setParentItem(0);
            pitchLineItem->setParentItem(0);
        }
    }

    void updateGraphicsItems()
    {
        pitchLabelItem->setPos(0.0f, location);
        pitchLabelItem->setText(label);
        pitchLabelItem->setColor(Qt::black);
        QPen pen(color);
        pen.setCosmetic(true);
        pitchLineItem->setPen(pen);
        pitchLineItem->setLine(QLineF(0.0f, location, 1.0f, location));
    }
};

PitchGridLine::PitchGridLine(QObject *parent)
    :   GridLine(*(new PitchGridLinePrivate(this)), parent)
{
    Q_D(PitchGridLine);
    d->init();
    setObjectName("PitchGridLine");
}

bool PitchGridLine::isVisible() const
{
    Q_D(const PitchGridLine);
    return d->pitchLineItem->isVisible();
}

void PitchGridLine::show()
{
    Q_D(PitchGridLine);
    d->pitchLabelItem->show();
    d->pitchLineItem->show();
}

void PitchGridLine::hide()
{
    Q_D(PitchGridLine);
    d->pitchLabelItem->hide();
    d->pitchLineItem->hide();
}

class ControlGridLinePrivate : public GridLinePrivate
{
public:
    ControlGridLinePrivate(ControlGridLine *q)
        :   GridLinePrivate(q)
    {}

    void init()
    {

    }

    ~ControlGridLinePrivate()
    {

    }

    void updateGraphicsParent()
    {

    }

    void updateGraphicsItems()
    {

    }
};

ControlGridLine::ControlGridLine(QObject *parent)
    :   GridLine(*(new ControlGridLinePrivate(this)), parent)
{
    Q_D(ControlGridLine);
    d->init();
    setObjectName("ControlGridLine");
}
