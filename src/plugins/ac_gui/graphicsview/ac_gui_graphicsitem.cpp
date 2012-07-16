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

#include "ac_gui_graphicsitem.h"

#include <ac_ientity.h>

#include <QFont>

namespace Ac {
namespace Gui {

class GraphicsCurveItemPrivate
{
public:
    GraphicsCurveItem *q;
    GraphicsGuideItem *guideItem;
    QGraphicsRectItem *noteHead;
    QColor color;

    GraphicsCurveItemPrivate(GraphicsCurveItem *q)
        :   q(q)
        ,   guideItem(new GraphicsGuideItem(q))
        ,   noteHead(new QGraphicsRectItem(q))
        ,   color(Qt::red)
    {
        noteHead->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        noteHead->setRect(-1.0f, -1.0f, 2.0f, 2.0f);
        noteHead->hide();
    }

    ~GraphicsCurveItemPrivate()
    {
        delete noteHead;
        delete guideItem;
    }

    void updateColor()
    {
        guideItem->setPen(QPen(QBrush(color), 0.0f, Qt::DotLine));
        QPen pen = q->pen();
        pen.setColor(color);
        q->setPen(pen);
        noteHead->setPen(pen);
        noteHead->setBrush(QBrush(color));
    }
};

GraphicsCurveItem::GraphicsCurveItem(QGraphicsItem *parent)
    :   GraphicsPathItem(parent)
    ,   d(new GraphicsCurveItemPrivate(this))
{
    QPen pen;
    pen.setCosmetic(true);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
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
    d->noteHead->setData(0, data);
}

void GraphicsCurveItem::setPoints(const PointList &points)
{
    if (points.count() < 2) {
        hide();
        d->guideItem->hide();
        d->noteHead->hide();
        return;
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
    d->noteHead->setPos(points.first().pos);
    d->noteHead->show();
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
    pen.setWidthF(3.0f);
    setPen(pen);
    d->guideItem->show();
}

void GraphicsCurveItem::unhighlight()
{
    QPen pen = this->pen();
    pen.setWidthF(1.0f);
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

QFont GraphicsTextItem::font() const
{
    return d->textItem->font();
}

void GraphicsTextItem::setFont(const QFont &font)
{
    d->textItem->setFont(font);
}

QString GraphicsTextItem::text() const
{
    return d->textItem->toPlainText();
}

void GraphicsTextItem::setText(const QString &text)
{
    d->textItem->setPlainText(text);
}

} // namespace Gui
} // namespace Ac
