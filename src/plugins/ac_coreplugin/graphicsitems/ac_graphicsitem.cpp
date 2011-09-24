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

#include "ac_graphicsitem.h"

class GraphicsCurveItemPrivate
{
public:
    GraphicsGuideItem *guideItem;

    GraphicsCurveItemPrivate(GraphicsCurveItem *q)
        :   guideItem(new GraphicsGuideItem(q))
    {}

    ~GraphicsCurveItemPrivate()
    {
        delete guideItem;
    }
};

GraphicsCurveItem::GraphicsCurveItem(QGraphicsItem *parent)
    :   GraphicsPathItem(parent)
    ,   d(new GraphicsCurveItemPrivate(this))
{
    setPen(QPen(Qt::red, 2.0f));
    unhighlight();
}

GraphicsCurveItem::~GraphicsCurveItem()
{
    delete d;
}

void GraphicsCurveItem::setPoints(const PointList &points)
{
    if (points.count() < 2) {
        setPath(QPainterPath());
        d->guideItem->setPath(QPainterPath());
    }
    QPainterPath curvePath(points.first().pos);
    QPainterPath guidePath;
    int n = points.count();
    for (int i = 1;  i < n;  ++i) {
        const Point &curPt = points.at(i);
        if ((Ac::NoCurve == curPt.curveType)
                || i == n - 1)
            curvePath.lineTo(curPt.pos);
        else {
            const Point &prevPt = points.at(i - 1);
            const Point &nextPt = points.at(i + 1);
            curvePath.quadTo(curPt.pos, nextPt.pos);
            guidePath.moveTo(prevPt.pos);
            guidePath.lineTo(curPt.pos);
            guidePath.lineTo(nextPt.pos);
            ++i;
        }
    }
    setPath(curvePath);
    d->guideItem->setPath(guidePath);
}

void GraphicsCurveItem::highlight()
{
    setPen(QPen(pen().color(), 4.0f));
    d->guideItem->show();
}

void GraphicsCurveItem::unhighlight()
{
    setPen(QPen(pen().color(), 2.0f));
    d->guideItem->hide();
}

class GraphicsTextItemPrivate
{
public:
    QGraphicsTextItem *textItem;

    GraphicsTextItemPrivate(GraphicsTextItem *q)
        :   textItem(new QGraphicsTextItem(q))
    {
        textItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }

    ~GraphicsTextItemPrivate()
    {
        delete textItem;
    }
};

GraphicsTextItem::GraphicsTextItem(QGraphicsItem *parent)
    :   GraphicsItem(parent)
    ,   d(new GraphicsTextItemPrivate(this))
{}

GraphicsTextItem::~GraphicsTextItem()
{
    delete d;
}

QColor GraphicsTextItem::color() const
{
    return d->textItem->defaultTextColor();
}

void GraphicsTextItem::setColor(const QColor &color)
{
    d->textItem->setDefaultTextColor(color);
}

QString GraphicsTextItem::text() const
{
    return d->textItem->toPlainText();
}

void GraphicsTextItem::setText(const QString &text)
{
    d->textItem->setPlainText(text);
}
