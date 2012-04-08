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

#ifndef AC_GRAPHICSITEM_H
#define AC_GRAPHICSITEM_H

#include <ac_point.h>

#include <QGraphicsItem>
#include <QPen>

class IEntity;

class GraphicsItem : public QGraphicsItem
{
public:
    GraphicsItem(QGraphicsItem *parent = 0)
        :   QGraphicsItem(parent)
    {
        setFlag(QGraphicsItem::ItemHasNoContents);
    }

    QRectF boundingRect() const
    {
        static QRectF r;
        return r;
    }

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
    {}
};

class GraphicsRootItem : public GraphicsItem
{
public:
    GraphicsRootItem(QGraphicsItem *parent = 0)
        :   GraphicsItem(parent)
    {
        setTransform(QTransform::fromScale(1.0f, -1.0f));
    }
};

class GraphicsPathItem : public QGraphicsPathItem
{
public:
    GraphicsPathItem(QGraphicsItem *parent = 0)
        :   QGraphicsPathItem(parent)
    {}

    QPainterPath shape() const
    {
        return path();
    }
};

class GraphicsGuideItem : public GraphicsPathItem
{
public:
    GraphicsGuideItem(QGraphicsItem *parent = 0)
        :   GraphicsPathItem(parent)
    {
        setFlag(QGraphicsItem::ItemStacksBehindParent);
        hide();
    }
};

class GraphicsCurveItemPrivate;
class GraphicsCurveItem : public GraphicsPathItem
{
    GraphicsCurveItemPrivate *d;

public:
    GraphicsCurveItem(QGraphicsItem *parent = 0);
    ~GraphicsCurveItem();

    void setEntity(IEntity *entity);
    void setPoints(const PointList &points);
    void setColor(const QColor &color);

    void highlight();
    void unhighlight();

    bool intersects(const QRectF &rect) const;
};

class GraphicsTextItemPrivate;
class GraphicsTextItem : public GraphicsItem
{
    GraphicsTextItemPrivate *d;

public:
    GraphicsTextItem(QGraphicsItem *parent = 0);
    ~GraphicsTextItem();

    QColor color() const;
    void setColor(const QColor &color);

    QFont font() const;
    void setFont(const QFont &font);

    QString text() const;
    void setText(const QString &text);
};

#endif // AC_GRAPHICSITEM_H
