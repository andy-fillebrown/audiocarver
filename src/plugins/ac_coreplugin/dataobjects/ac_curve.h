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

#include "ac_graphicsobject.h"
#include "ac_ientity.h"

#include <ac_graphicsitem.h>
#include <ac_point.h>

#include <QStack>

class GraphicsCurveItem;
class ScoreObject;

class AC_CORE_EXPORT Curve : public GraphicsObject
{
    Q_DECLARE_AGGREGATOR(Curve, GraphicsObject)
    QScopedPointer<GraphicsCurveItem> _graphicsCurveItem;

    Q_DECLARE_ROLECOUNT(1)
    QStack<PointList> _pointsStack;

protected:
    Curve() {}

    virtual ScoreObject *scoreObject() const = 0;
    virtual void conformPoints() = 0;

    GraphicsCurveItem *graphicsCurveItem() const
    {
        return qGetPtrHelper(_graphicsCurveItem);
    }

    QStack<PointList> &pointsStack()
    {
        return _pointsStack;
    }

    PointList &points()
    {
        return _pointsStack.top();
    }

    bool setPoints(const PointList &points)
    {
        PointList new_pts = points;
        while (1 < _pointsStack.count())
            _pointsStack.pop();
        PointList old_pts = _pointsStack.top();
        _pointsStack.top() = new_pts;
        conformPoints();
        new_pts = _pointsStack.top();
        _pointsStack.top() = old_pts;
        if (_pointsStack.top() == new_pts)
            return false;
        Q_MI_SCOPED_CHANGE(Ac::PointsRole);
        _pointsStack.top() = new_pts;
        updateGraphicsItems();
        return true;
    }

    void updateGraphicsItems();

    void setColor(const QColor &color)
    {
        graphicsCurveItem()->setColor(color);
    }

    // GraphicsObject

    GraphicsParent *graphicsParent() const;

    // IAggregator

    void *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case Ac::EntityInterface:
            return appendAggregate(Q_CREATE_AGGREGATE(Entity));
        default:
            return Base::createAggregate(interfaceType);
        }
    }

    class Entity : public IEntity
    {
        Q_DECLARE_BASE_AGGREGATE(Entity)

        // IEntity

        void highlight()
        {
            a()->graphicsCurveItem()->highlight();
        }

        void unhighlight()
        {
            a()->graphicsCurveItem()->unhighlight();
        }

        bool intersects(const QRectF &rect) const
        {
            return a()->graphicsCurveItem()->intersects(rect);
        }

        bool isVisible() const
        {
            return a()->graphicsCurveItem()->isVisible();
        }
    };

    class SubEntity : public ISubEntity
    {
        Q_DECLARE_BASE_AGGREGATE(SubEntity)

        // ISubEntity

        bool isCurve() const
        {
            return true;
        }
    };

    class Points : public IPoints
    {
        Q_DECLARE_BASE_AGGREGATE(Points)

        // IPoints

        const PointList &points() const
        {
            return a()->pointsStack().top();
        }

        void pushPoints(const PointList &points)
        {
            Q_A(Curve);
            a->pointsStack().push(points);
            a->updateGraphicsItems();
        }

        void popPoints()
        {
            Q_A(Curve);
            a->pointsStack().pop();
            a->updateGraphicsItems();
        }

        void setPoints(const PointList &points)
        {
            a()->setPoints(points);
        }
    };

    class ModelData : public Base::ModelData
    {
    public:
        Q_DECLARE_MODELDATA
        Q_DECLARE_MODELDATA_FUNCTIONS

        // IModelData

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::PointsRole:
                return QVariant::fromValue(a()->points());
            default:
                return Base::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::PointsRole:
                return a()->setPoints(qvariant_cast<PointList>(data));
            default:
                return Base::setVariant(data, role);
            }
        }
    };
};

#endif // AC_CURVE_H
