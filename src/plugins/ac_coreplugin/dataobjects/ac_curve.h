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

#ifndef AC_CURVE_H
#define AC_CURVE_H

#include <ac_ientity.h>
#include <ac_graphicsobject.h>
#include <ac_point.h>

#include <QStack>

class GraphicsCurveItem;
class ScoreObject;

class CurvePrivate;
class AC_CORE_EXPORT Curve : public GraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(PointList points READ points WRITE setPoints)
    Q_DECLARE_PRIVATE(Curve)

public:
    inline const PointList &points() const;
    void setPoints(const PointList &points);

    virtual ScoreObject *scoreObject() const = 0;

    void setColor(const QColor &color);

protected:
    inline Curve(CurvePrivate &dd, QObject *parent);

    inline void *queryInterface(int interface) const;
};

class CurvePrivate : public GraphicsObjectPrivate
{
    QScopedPointer<GraphicsCurveItem> _graphicsCurveItem;
    QScopedPointer<IEntity> _entity;
    QScopedPointer<ISubEntity> _subEntity;
    QScopedPointer<IPoints> _points;

public:
    QStack<PointList> pointsStack;

    class Entity : public IEntity
    {
    public:
        Curve *q_ptr;

        Entity(Curve *q)
            :   q_ptr(q)
        {}

        void highlight();
        void unhighlight();
        bool intersects(const QRectF &rect) const;
        bool isVisible() const;

        Q_MI_DEFINE_QUERYINTERFACE
        Q_DECLARE_PUBLIC(Curve)
    };

    class SubEntity : public ISubEntity
    {
    public:
        Curve *q_ptr;

        SubEntity(Curve *q)
            :   q_ptr(q)
        {}

        bool isCurve() const
        {
            return true;
        }

        Q_MI_DEFINE_QUERYINTERFACE
        Q_DECLARE_PUBLIC(Curve)
    };

    class Points : public IPoints
    {
    public:
        Curve *q_ptr;

        Points(Curve *q)
            :   q_ptr(q)
        {}

        const PointList &points() const
        {
            Q_MI_D(const Curve);
            return d->pointsStack.top();
        }

        void pushPoints(const PointList &points)
        {
            Q_MI_D(Curve);
            d->pointsStack.push(points);
            d->updateGraphicsItems();
        }

        void popPoints()
        {
            Q_MI_D(Curve);
            d->pointsStack.pop();
            d->updateGraphicsItems();
        }

        void setPoints(const PointList &points)
        {
            q_func()->setPoints(points);
        }

        Q_MI_DEFINE_QUERYINTERFACE
        Q_DECLARE_PUBLIC(Curve)
    };

    class ModelItem : public GraphicsObjectPrivate::ModelItem
    {
    public:
        ModelItem(Object *q)
            :   GraphicsObjectPrivate::ModelItem(q)
        {}

        int roleAt(int i) const
        {
            if (Curve::staticMetaObject.propertyOffset() == i)
                return Ac::PointsRole;
            return GraphicsObjectPrivate::ModelItem::roleAt(i);
        }

        QVariant data(int role) const;
        bool setData(const QVariant &data, int role);
    };

    CurvePrivate(Curve *q, ModelItem *modelItem, SubEntity *subEntity);
    void init();

    GraphicsCurveItem *graphicsCurveItem() const
    {
        return qGetPtrHelper(_graphicsCurveItem);
    }

    IEntity *entity() const
    {
        return qGetPtrHelper(_entity);
    }

    ISubEntity *subEntity() const
    {
        return qGetPtrHelper(_subEntity);
    }

    IPoints *points() const
    {
        return qGetPtrHelper(_points);
    }

    GraphicsParentPrivate *graphicsParent() const;
    void updateGraphicsItems();

    virtual void conformPoints() = 0;

    Q_DECLARE_PUBLIC(Curve)
};

inline Curve::Curve(CurvePrivate &dd, QObject *parent)
    :   GraphicsObject(dd, parent)
{
    dd.init();
}

inline const PointList &Curve::points() const
{
    return d_func()->pointsStack.top();
}

inline void *Curve::queryInterface(int interface) const
{
    switch (interface) {
    case Ac::EntityInterface:
        return d_func()->entity();
    case Ac::SubEntityInterface:
        return d_func()->subEntity();
    case Ac::PointsInterface:
        return d_func()->points();
    default:
        return GraphicsObject::queryInterface(interface);
    }
}

#endif // AC_CURVE_H
