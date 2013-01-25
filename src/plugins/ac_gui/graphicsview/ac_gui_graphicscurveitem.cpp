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

#include "ac_gui_graphicscurveitem.h"
#include "ac_gui_graphicsguideitem.h"
#include <ac_core_constants.h>
#include <QPen>

using namespace Ac;
using namespace Qt;

GraphicsCurveItem::GraphicsCurveItem(QGraphicsItem *parent)
    :   GraphicsPathItem(parent)
    ,   _guideItem(new GraphicsGuideItem(this))
    ,   _noteHead(new QGraphicsRectItem(this))
{
    _noteHead->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    _noteHead->setRect(-1.0f, -1.0f, 2.0f, 2.0f);
    _noteHead->hide();
    QPen pen;
    pen.setCosmetic(true);
    pen.setCapStyle(FlatCap);
    pen.setJoinStyle(MiterJoin);
    setPen(pen);
    setColor(DEFAULT_TRACK_COLOR);
    highlight(false);
}

bool GraphicsCurveItem::intersects(const QRectF &rect) const
{
    QPainterPathStroker stroker;
    stroker.setWidth(Q_FLOAT_MIN);
    QPainterPath stroke = stroker.createStroke(path());
    return stroke.intersects(rect);
}

void GraphicsCurveItem::setEntity(IEntity *entity)
{
    const QVariant data = quintptr(entity);
    setData(0, data);
    _guideItem->setData(0, data);
    _noteHead->setData(0, data);
}

void GraphicsCurveItem::setPoints(const PointList &points)
{
    if (points.count() < 2) {
        hide();
        _guideItem->hide();
        _noteHead->hide();
        return;
    }
    QPainterPath curvePath(points.first().pos);
    QPainterPath guidePath;
    int n = points.count();
    for (int i = 1;  i < n;  ++i) {
        const Point &curPt = points.at(i);
        if ((NoCurve == curPt.curveType)
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
    _guideItem->setPath(guidePath);
    _noteHead->setPos(points.first().pos);
    _noteHead->show();
}

void GraphicsCurveItem::setColor(const QColor &color)
{
    _guideItem->setPen(QPen(QBrush(color), 0.0f, DotLine));
    QPen pen = this->pen();
    pen.setColor(color);
    setPen(pen);
    _noteHead->setPen(pen);
    _noteHead->setBrush(QBrush(color));
}

void GraphicsCurveItem::highlight(bool on)
{
    QPen pen = this->pen();
    if (on) {
        pen.setWidthF(3.0f);
        _guideItem->show();
    } else {
        pen.setWidth(1.0f);
        _guideItem->hide();
    }
    setPen(pen);
}
