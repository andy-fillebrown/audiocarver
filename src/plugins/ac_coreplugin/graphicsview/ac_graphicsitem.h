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

class IEntity;

class GraphicsItem : public QGraphicsItem
{
public:
    explicit GraphicsItem(QGraphicsItem *parent = 0)
        :   QGraphicsItem(parent)
    {
        setFlag(QGraphicsItem::ItemHasNoContents);
    }

    QRectF boundingRect() const { static QRectF r;  return r; }
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
};

class GraphicsRootItem : public GraphicsItem
{
public:
    explicit GraphicsRootItem(QGraphicsItem *parent = 0)
        :   GraphicsItem(parent)
    {
        setTransform(QTransform::fromScale(1.0f, -1.0f));
    }
};

class GraphicsPathItem : public QGraphicsPathItem
{
public:
    explicit GraphicsPathItem(QGraphicsItem *parent = 0)
        :   QGraphicsPathItem(parent)
    {}

    QPainterPath shape() const { return path(); }
};

class GraphicsGuideItem : public GraphicsPathItem
{
public:
    explicit GraphicsGuideItem(QGraphicsItem *parent = 0)
        :   GraphicsPathItem(parent)
    {
        setFlag(QGraphicsItem::ItemStacksBehindParent);
        hide();
    }
};

class GraphicsCurveItemPrivate;
class GraphicsCurveItem : public GraphicsPathItem
{
public:
    explicit GraphicsCurveItem(QGraphicsItem *parent = 0);
    ~GraphicsCurveItem();

    void setEntity(IEntity *entity);
    void setPoints(const PointList &points);
    void setColor(const QColor &color);

    void highlight();
    void unhighlight();

    bool intersects(const QRectF &rect) const;

private:
    Q_DISABLE_COPY(GraphicsCurveItem)
    GraphicsCurveItemPrivate *d;
};

class GraphicsTextItemPrivate;
class GraphicsTextItem : public GraphicsItem
{
public:
    explicit GraphicsTextItem(QGraphicsItem *parent = 0);
    ~GraphicsTextItem();

    QColor color() const;
    void setColor(const QColor &color);

    QString text() const;
    void setText(const QString &text);

private:
    Q_DISABLE_COPY(GraphicsTextItem)
    GraphicsTextItemPrivate *d;
};

#endif // AC_GRAPHICSITEM_H
