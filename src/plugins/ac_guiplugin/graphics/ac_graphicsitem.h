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
        qDeleteAll(_points);
    }

    const GraphicsCurvePointItems &points() const { return _points; }
    void setPoints(const PointList &points)
    {
        qDeleteAll(_points);
        _points.reserve(points.count());
        foreach (const Point &point, points) {
            GraphicsCurvePointItem *pointItem = new GraphicsCurvePointItem;
            pointItem->setPos(point.pos);
            pointItem->setParentItem(this);
            _points.append(pointItem);
        }
        if (points.count() < 2) {
            setPath(QPainterPath());
            _guideItem->setPath(QPainterPath());
        }
        QPainterPath curvePath(points[0].pos);
        QPainterPath guidePath;
        for (int i = 1;  i < points.count();  ++i) {
            if ((NoCurve == points[i].curveType)
                    || i == points.count() - 1)
                curvePath.lineTo(points[i].pos);
            else {
                curvePath.quadTo(points[i].pos, points[i + 1].pos);
                guidePath.moveTo(points[i - 1].pos);
                guidePath.lineTo(points[i].pos);
                guidePath.lineTo(points[i + 1].pos);
                ++i;
            }
        }
        setPath(curvePath);
        _guideItem->setPath(guidePath);
    }

    void highlight()
    {
        setPen(QPen(QBrush(Qt::red), 4.0f));
        foreach (GraphicsPointItem *point, _points)
            point->highlight();
        _guideItem->show();
    }

    void unhighlight()
    {
        _guideItem->hide();
        foreach (GraphicsPointItem *point, _points)
            point->unhighlight();
        setPen(QPen(QBrush(Qt::red), 2.0f));
    }

private:
    GraphicsCurvePointItems _points;
    GraphicsGuideItem *_guideItem;
};

class GraphicsLabelItem : public GraphicsItem
{
public:
    GraphicsLabelItem()
        :   _textItem(new QGraphicsTextItem(this))
    {
        _textItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }

    QColor color() const { return _textItem->defaultTextColor(); }
    void setColor(const QColor &color) { _textItem->setDefaultTextColor(color); }

    QString text() const { return _textItem->toPlainText(); }
    void setText(const QString &text) { _textItem->setPlainText(text); }

private:
    QGraphicsTextItem *_textItem;
};

#endif // AC_GRAPHICSITEM_H
