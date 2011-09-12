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

#ifndef AC_GRAPHICSITEM_H
#define AC_GRAPHICSITEM_H

#include <ac_point.h>

#include <QGraphicsItem>
#include <QPen>

class GraphicsItem : public QGraphicsItem
{
public:
    QRectF boundingRect() const
    {
        static QRectF r;
        return r;
    }

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
};

class GraphicsRootItem : public GraphicsItem
{
public:
    GraphicsRootItem()
    {
        setTransform(QTransform::fromScale(1.0f, -1.0f));
    }
};

class GraphicsGripItem : public QGraphicsRectItem
{
public:
    enum { Type = QGraphicsItem::UserType + 1 };

    GraphicsGripItem()
    {
        setFlag(QGraphicsItem::ItemIgnoresTransformations);
        setPen(QPen(Qt::blue));
        setBrush(QBrush(Qt::blue));
        setRect(-3.0f, -3.0f, 6.0f, 6.0f);
        setZValue(1.0f);
    }

    virtual int type() const { return Type; }
};

class GraphicsPointItem : public GraphicsItem
{
public:
    GraphicsPointItem()
        :   _gripItem(new GraphicsGripItem)
    {
        _gripItem->setParentItem(this);
        _gripItem->hide();
    }

    void highlight()
    {
        _gripItem->show();
    }

    void unhighlight()
    {
        _gripItem->hide();
    }

private:
    GraphicsGripItem *_gripItem;
};

class GraphicsCurvePointItem : public GraphicsPointItem
{
public:
    CurveType curveType() const
    {
        return BezierCurve;
    }
};

typedef QList<GraphicsCurvePointItem*> GraphicsCurvePointItems;

class GraphicsPathItem : public QGraphicsPathItem
{
public:
    GraphicsPathItem()
    {
        setBoundingRegionGranularity(1.0f);
    }

    QPainterPath shape() const { return path(); }
};

class GraphicsGuideItem : public GraphicsPathItem
{
public:
    GraphicsGuideItem()
    {
        setFlag(QGraphicsItem::ItemStacksBehindParent);
        setPen(QPen(QBrush(Qt::lightGray), 0.0f, Qt::DotLine));
        hide();
    }
};

class GraphicsCurveItem : public GraphicsPathItem
{
public:
    GraphicsCurveItem()
        :   _guideItem(new GraphicsGuideItem)
    {
        _guideItem->setParentItem(this);
        unhighlight();
    }

    ~GraphicsCurveItem()
    {
        delete _guideItem;
    }

    const GraphicsCurvePointItems &points() const { return _points; }

    void appendPoint(GraphicsCurvePointItem *point)
    {
        if (_points.contains(point))
            return;
        _points.append(point);
        point->setParentItem(this);
    }

    void removePoint(GraphicsCurvePointItem *point)
    {
        point->setParentItem(0);
        _points.removeOne(point);
    }

    virtual void update()
    {
        if (_points.count() < 2) {
            setPath(QPainterPath());
            _guideItem->setPath(QPainterPath());
            return;
        }
        QPainterPath curvePath(_points[0]->pos());
        QPainterPath guidePath;
        for (int i = 1;  i < _points.count();  ++i) {
            if ((NoCurve == _points[i]->curveType())
                    || i == _points.count() - 1)
                curvePath.lineTo(_points[i]->pos());
            else {
                curvePath.quadTo(_points[i]->pos(), _points[i + 1]->pos());
                guidePath.moveTo(_points[i - 1]->pos());
                guidePath.lineTo(_points[i]->pos());
                guidePath.lineTo(_points[i + 1]->pos());
                ++i;
            }
        }
        setPath(curvePath);
        _guideItem->setPath(guidePath);
    }

    void highlight()
    {
        setPen(QPen(QBrush(Qt::red), 4.0f));
        foreach (GraphicsPointItem *pt, _points)
            pt->highlight();
        _guideItem->show();
    }

    void unhighlight()
    {
        _guideItem->hide();
        foreach (GraphicsPointItem *pt, _points)
            pt->unhighlight();
        setPen(QPen(QBrush(Qt::red), 2.0f));
    }

private:
    GraphicsCurvePointItems _points;
    GraphicsGuideItem *_guideItem;
};

#endif // AC_GRAPHICSITEM_H
