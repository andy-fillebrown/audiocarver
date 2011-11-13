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

#include <ac_ientity.h>

class GraphicsCurveItemPrivate
{
public:
    GraphicsCurveItem *q;
    GraphicsGuideItem *guideItem;
    QColor color;

    GraphicsCurveItemPrivate(GraphicsCurveItem *q)
        :   q(q)
        ,   guideItem(new GraphicsGuideItem(q))
        ,   color(Qt::red)
    {}

    ~GraphicsCurveItemPrivate()
    {
        delete guideItem;
    }

    void updateColor()
    {
        guideItem->setPen(QPen(QBrush(color), 0.0f, Qt::DotLine));
        QPen pen = q->pen();
        pen.setColor(color);
        q->setPen(pen);
    }
};

GraphicsCurveItem::GraphicsCurveItem(QGraphicsItem *parent)
    :   GraphicsPathItem(parent)
    ,   d(new GraphicsCurveItemPrivate(this))
{
    QPen pen;
    pen.setCosmetic(true);
    pen.setCapStyle(Qt::RoundCap);
    setPen(pen);
    d->updateColor();
    unhighlight();
}

GraphicsCurveItem::~GraphicsCurveItem()
{
    delete d;
}

void GraphicsCurveItem::setEntity(IEntity *entity)
{
    const QVariant data = quintptr(entity);
    setData(0, data);
    d->guideItem->setData(0, data);
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

void GraphicsCurveItem::setColor(const QColor &color)
{
    if (d->color == color)
        return;
    d->color = color;
    d->updateColor();
}

void GraphicsCurveItem::highlight()
{
    QPen pen = this->pen();
    pen.setWidthF(5.0f);
    setPen(pen);
    d->guideItem->show();
}

void GraphicsCurveItem::unhighlight()
{
    QPen pen = this->pen();
    pen.setWidthF(3.0f);
    setPen(pen);
    d->guideItem->hide();
}

bool GraphicsCurveItem::intersects(const QRectF &rect) const
{
    QPainterPathStroker stroker;
    stroker.setWidth(Q_FLOAT_MIN);
    QPainterPath stroke = stroker.createStroke(path());
    return stroke.intersects(rect);
}

class GraphicsTextItemPrivate
{
public:
    QGraphicsTextItem *textItem;

    GraphicsTextItemPrivate(GraphicsTextItem *q)
        :   textItem(new QGraphicsTextItem(q))
    {
        textItem->setCacheMode(QGraphicsItem::ItemCoordinateCache);
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
