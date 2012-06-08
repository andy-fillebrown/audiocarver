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

#include "ac_database_gridline.h"

#include <mi_scopeddatachange.h>

namespace Database {

IAggregator *GridLine::init()
{
    return Object::init();
}

bool GridLine::setLocation(qreal location)
{
    location = qMax(qreal(0.0f), location);
    if (_location == location)
        return false;
    ScopedDataChange data_change(this, Ac::LocationRole);
    _location = location;
    return true;
}

bool GridLine::setLabel(const QString &label)
{
    if (_label == label)
        return false;
    ScopedDataChange data_change(this, Ac::LabelRole);
    _label = label;
    return true;
}

bool GridLine::setPriority(int priority)
{
    priority = qMax(0, priority);
    if (_priority == priority)
        return false;
    ScopedDataChange data_change(this, Ac::PriorityRole);
    _priority = priority;
    return true;
}

bool GridLine::setColor(int color)
{
    color = qBound(0x000000, color, 0xffffff);
    if (_color == color)
        return false;
    ScopedDataChange data_change(this, Ac::ColorRole);
    _color = color;
    return true;
}

IAggregate *GridLine::ModelData::init()
{
    return Object::ModelData::init();
}

IAggregate *GridLine::ModelItem::init()
{
    return Object::ModelItem::init();
}

} // namespace Database

//#include "ac_gridline.h"

//#include <ac_gridsettings.h>

//#include <QFont>
//#include <QGraphicsItem>
//#include <QPalette>

//static const QFont &gridLabelFont()
//{
//    static QFont font;
//    static bool initialized = false;
//    if (!initialized) {
//        font.setPointSize(6);
//        initialized = true;
//    }
//    return font;
//}

//static Qt::PenStyle gridLinePenStyle()
//{
//    static Qt::PenStyle style = Qt::DotLine;
//    return style;
//}

//static Qt::PenStyle gridLineExtPenStyle()
//{
//    static Qt::PenStyle style = Qt::DotLine;
//    return style;
//}

//GridLinePrivate::GridLinePrivate(GridLine *q)
//    :   GraphicsObjectPrivate(q)
//    ,   location(0.0f)
//    ,   priority(0)
//    ,   color(Qt::lightGray)
//{}

//GraphicsParentPrivate *GridLinePrivate::graphicsParent() const
//{
//    Q_Q(const GridLine);
//    GridSettings *gridSettings = q->gridSettings();
//    return gridSettings ? gridSettings->d_func() : 0;
//}

//GridLine::GridLine(GridLinePrivate &dd, QObject *parent)
//    :   GraphicsObject(dd, parent)
//{}

//qreal GridLine::location() const
//{
//    Q_D(const GridLine);
//    return d->location;
//}

//void GridLine::setLocation(qreal location)
//{
//    Q_D(GridLine);
//    if (location < 0.0f)
//        location = 0.0f;
//    if (d->location == location)
//        return;
//    d->beginChangeData();
//    d->location = location;
//    d->updateGraphicsItems();
//    d->endChangeData();
//}

//const QString &GridLine::label() const
//{
//    Q_D(const GridLine);
//    return d->label;
//}

//void GridLine::setLabel(const QString &label)
//{
//    Q_D(GridLine);
//    if (d->label == label)
//        return;
//    d->beginChangeData();
//    d->label = label;
//    d->updateGraphicsItems();
//    d->endChangeData();
//}

//int GridLine::priority() const
//{
//    Q_D(const GridLine);
//    return d->priority;
//}

//void GridLine::setPriority(int priority)
//{
//    Q_D(GridLine);
//    if (d->priority == priority)
//        return;
//    d->beginChangeData();
//    d->priority = priority;
//    d->updateGraphicsItems();
//    d->endChangeData();
//}

//const QColor &GridLine::color() const
//{
//    Q_D(const GridLine);
//    return d->color;
//}

//void GridLine::setColor(const QColor &color)
//{
//    Q_D(GridLine);
//    if (d->color == color)
//        return;
//    d->beginChangeData();
//    d->color = color;
//    d->updateGraphicsItems();
//    d->endChangeData();
//}

//GridSettings *GridLine::gridSettings() const
//{
//    QObject *parent = QObject::parent();
//    return parent ? object_cast<GridSettings>(parent->parent()) : 0;
//}

//class TimeGridLinePrivate : public GridLinePrivate
//{
//public:
//    GraphicsTextItem *timeLabelItem;
//    QGraphicsLineItem *timeLineItem;
//    QGraphicsLineItem *pitchLineItem;
//    QGraphicsLineItem *pitchLineLoExtItem;
//    QGraphicsLineItem *pitchLineHiExtItem;
//    QGraphicsLineItem *controlLineItem;
//    QGraphicsLineItem *controlLineHiExtItem;

//    TimeGridLinePrivate(TimeGridLine *q)
//        :   GridLinePrivate(q)
//        ,   timeLabelItem(new GraphicsTextItem)
//        ,   timeLineItem(new QGraphicsLineItem)
//        ,   pitchLineItem(new QGraphicsLineItem)
//        ,   pitchLineLoExtItem(new QGraphicsLineItem(pitchLineItem))
//        ,   pitchLineHiExtItem(new QGraphicsLineItem(pitchLineItem))
//        ,   controlLineItem(new QGraphicsLineItem)
//        ,   controlLineHiExtItem(new QGraphicsLineItem(controlLineItem))
//    {
//        timeLabelItem->setFont(gridLabelFont());
//    }

//    void init()
//    {
//        updateGraphicsParent();
//        updateGraphicsItems();
//    }

//    ~TimeGridLinePrivate()
//    {
//        delete controlLineItem;
//        delete pitchLineItem;
//        delete timeLineItem;
//        delete timeLabelItem;
//    }

//    void updateGraphicsParent()
//    {
//        GraphicsParentPrivate *parent = graphicsParent();
//        if (parent) {
//            timeLabelItem->setParentItem(parent->mainGraphicsItems[Ac::TimeLabelScene]);
//            timeLineItem->setParentItem(parent->mainGraphicsItems[Ac::TimeLabelScene]);
//            pitchLineItem->setParentItem(parent->unitYGraphicsItems[Ac::PitchScene]);
//            controlLineItem->setParentItem(parent->mainGraphicsItems[Ac::ControlScene]);
//        } else {
//            timeLabelItem->setParentItem(0);
//            timeLineItem->setParentItem(0);
//            pitchLineItem->setParentItem(0);
//            controlLineItem->setParentItem(0);
//        }
//    }

//    void updateGraphicsItems()
//    {
//        timeLabelItem->setPos(location, 0.0f);
//        timeLabelItem->setText(label);
//        timeLabelItem->setColor(Qt::black);
//        QPen pen(color);
//        pen.setCosmetic(true);
//        pen.setStyle(gridLinePenStyle());
//        pitchLineItem->setPen(pen);
//        controlLineItem->setPen(pen);
//        pen.setStyle(gridLineExtPenStyle());
//        timeLineItem->setPen(pen);
//        pitchLineLoExtItem->setPen(pen);
//        pitchLineHiExtItem->setPen(pen);
//        controlLineHiExtItem->setPen(pen);
//        timeLineItem->setLine(location, -10.0f, location, 10.0f);
//        pitchLineItem->setLine(location, 0.0f, location, 1.0f);
//        pitchLineLoExtItem->setLine(location, -1.0f, location, 0.0f);
//        pitchLineHiExtItem->setLine(location, 1.0f, location, 2.0f);
//        controlLineItem->setLine(location, 0.0f, location, 1.0f);
//        controlLineHiExtItem->setLine(location, 1.0f, location, 2.0f);
//    }
//};

//TimeGridLine::TimeGridLine(QObject *parent)
//    :   GridLine(*(new TimeGridLinePrivate(this)), parent)
//{
//    Q_D(TimeGridLine);
//    d->init();
//    setName("TimeGridLine");
//}

//bool TimeGridLine::isVisible() const
//{
//    Q_D(const TimeGridLine);
//    return d->pitchLineItem->isVisible();
//}

//void TimeGridLine::show()
//{
//    Q_D(TimeGridLine);
//    d->timeLabelItem->show();
//    d->timeLineItem->show();
//    d->pitchLineItem->show();
//    d->controlLineItem->show();
//}

//void TimeGridLine::hide()
//{
//    Q_D(TimeGridLine);
//    d->timeLabelItem->hide();
//    d->timeLineItem->hide();
//    d->pitchLineItem->hide();
//    d->controlLineItem->hide();
//}

//int TimeGridLine::type() const
//{
//    return Type;
//}

//class PitchGridLinePrivate : public GridLinePrivate
//{
//public:
//    GraphicsTextItem *pitchLabelItem;
//    QGraphicsLineItem *pitchLineItem;
//    QGraphicsLineItem *pitchLineRightExtItem;

//    PitchGridLinePrivate(PitchGridLine *q)
//        :   GridLinePrivate(q)
//        ,   pitchLabelItem(new GraphicsTextItem)
//        ,   pitchLineItem(new QGraphicsLineItem)
//        ,   pitchLineRightExtItem(new QGraphicsLineItem(pitchLineItem))
//    {
//        pitchLabelItem->setFont(gridLabelFont());
//    }

//    void init()
//    {
//        updateGraphicsParent();
//        updateGraphicsItems();
//    }

//    ~PitchGridLinePrivate()
//    {
//        delete pitchLineItem;
//        delete pitchLabelItem;
//    }

//    void updateGraphicsParent()
//    {
//        GraphicsParentPrivate *parent = graphicsParent();
//        if (parent) {
//            pitchLabelItem->setParentItem(parent->mainGraphicsItems[Ac::PitchLabelScene]);
//            pitchLineItem->setParentItem(parent->unitXGraphicsItems[Ac::PitchScene]);
//        } else {
//            pitchLabelItem->setParentItem(0);
//            pitchLineItem->setParentItem(0);
//        }
//    }

//    void updateGraphicsItems()
//    {
//        pitchLabelItem->setPos(0.0f, location);
//        pitchLabelItem->setText(label);
//        pitchLabelItem->setColor(Qt::black);
//        QPen pen(color);
//        pen.setCosmetic(true);
//        pen.setStyle(gridLinePenStyle());
//        pitchLineItem->setPen(pen);
//        pen.setStyle(gridLineExtPenStyle());
//        pitchLineRightExtItem->setPen(pen);
//        pitchLineItem->setLine(0.0f, location, 1.0f, location);
//        pitchLineRightExtItem->setLine(1.0f, location, 2.0f, location);
//    }
//};

//PitchGridLine::PitchGridLine(QObject *parent)
//    :   GridLine(*(new PitchGridLinePrivate(this)), parent)
//{
//    Q_D(PitchGridLine);
//    d->init();
//    setName("PitchGridLine");
//}

//bool PitchGridLine::isVisible() const
//{
//    Q_D(const PitchGridLine);
//    return d->pitchLineItem->isVisible();
//}

//void PitchGridLine::show()
//{
//    Q_D(PitchGridLine);
//    d->pitchLabelItem->show();
//    d->pitchLineItem->show();
//}

//void PitchGridLine::hide()
//{
//    Q_D(PitchGridLine);
//    d->pitchLabelItem->hide();
//    d->pitchLineItem->hide();
//}

//int PitchGridLine::type() const
//{
//    return Type;
//}

//class ControlGridLinePrivate : public GridLinePrivate
//{
//public:
//    GraphicsTextItem *controlLabelItem;
//    QGraphicsLineItem *controlLineItem;
//    QGraphicsLineItem *controlLineRightExtItem;

//    ControlGridLinePrivate(ControlGridLine *q)
//        :   GridLinePrivate(q)
//        ,   controlLabelItem(new GraphicsTextItem)
//        ,   controlLineItem(new QGraphicsLineItem)
//        ,   controlLineRightExtItem(new QGraphicsLineItem(controlLineItem))
//    {
//        controlLabelItem->setFont(gridLabelFont());
//    }

//    void init()
//    {
//        updateGraphicsParent();
//        updateGraphicsItems();
//    }

//    ~ControlGridLinePrivate()
//    {
//        delete controlLineItem;
//        delete controlLabelItem;
//    }

//    void updateGraphicsParent()
//    {
//        GraphicsParentPrivate *parent = graphicsParent();
//        if (parent) {
//            controlLabelItem->setParentItem(parent->mainGraphicsItems[Ac::ControlLabelScene]);
//            controlLineItem->setParentItem(parent->unitXGraphicsItems[Ac::ControlScene]);
//        } else {
//            controlLabelItem->setParentItem(0);
//            controlLineItem->setParentItem(0);
//        }
//    }

//    void updateGraphicsItems()
//    {
//        controlLabelItem->setPos(0.0f, location);
//        controlLabelItem->setText(label);
//        controlLabelItem->setColor(Qt::black);
//        QPen pen(color);
//        pen.setCosmetic(true);
//        pen.setStyle(gridLinePenStyle());
//        controlLineItem->setPen(pen);
//        pen.setStyle(gridLineExtPenStyle());
//        controlLineRightExtItem->setPen(pen);
//        controlLineItem->setLine(0.0f, location, 1.0f, location);
//        controlLineRightExtItem->setLine(1.0f, location, 2.0f, location);
//    }
//};

//ControlGridLine::ControlGridLine(QObject *parent)
//    :   GridLine(*(new ControlGridLinePrivate(this)), parent)
//{
//    Q_D(ControlGridLine);
//    d->init();
//    setName("ControlGridLine");
//}

//bool ControlGridLine::isVisible() const
//{
//    Q_D(const ControlGridLine);
//    return d->controlLineItem->isVisible();
//}

//void ControlGridLine::show()
//{
//    Q_D(ControlGridLine);
//    d->controlLabelItem->show();
//    d->controlLineItem->show();
//}

//void ControlGridLine::hide()
//{
//    Q_D(ControlGridLine);
//    d->controlLabelItem->hide();
//    d->controlLineItem->hide();
//}

//int ControlGridLine::type() const
//{
//    return Type;
//}
