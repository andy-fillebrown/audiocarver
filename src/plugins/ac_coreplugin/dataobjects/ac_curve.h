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
    Q_I_DERIVED__AGGREGATOR(Curve, GraphicsObject)
    QScopedPointer<GraphicsCurveItem> _graphicsCurveItem;

    Q_I_DERIVED__AGGREGATOR__ROLE_COUNT(1)
    QStack<PointList> _pointsStack;

protected:
    Curve() {}

    virtual ScoreObject *scoreObject() const = 0;
    virtual void conformPoints() = 0;

    GraphicsCurveItem *graphicsCurveItem() const
    {
        return qGetPtrHelper(_graphicsCurveItem);
    }

    PointList &points()
    {
        return _pointsStack.top();
    }

    void pushPoints(const PointList &points)
    {
        Q_DATA_CHANGE((Ac::PointsRole, Mi::NotifyParent))
        _pointsStack.push(points);
        updateGraphicsItems();
    }

    void popPoints()
    {
        if (1 == _pointsStack.count())
            return;
        Q_DATA_CHANGE((Ac::PointsRole, Mi::NotifyParent))
        _pointsStack.pop();
        updateGraphicsItems();
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
        Q_DATA_CHANGE((Ac::PointsRole, Mi::NotifyModelAndParent));
        _pointsStack.top() = new_pts;
        updateGraphicsItems();
        return true;
    }

    virtual void updateGraphicsItems();

    void setColor(const QColor &color)
    {
        graphicsCurveItem()->setColor(color);
    }

    // GraphicsObject
    GraphicsParent *graphicsParent() const;

    // IEntity
    class Entity : public IEntity
    {
        Q_I_BASE__AGGREGATE(Entity)

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

    // ISubEntity
    class SubEntity : public ISubEntity
    {
        Q_I_BASE__AGGREGATE(SubEntity)

        bool isCurve() const
        {
            return true;
        }
    };

    // IPoints
    class Points : public IPoints
    {
        Q_I_BASE__AGGREGATE(Points)

        const PointList &points() const
        {
            return a()->points();
        }

        void pushPoints(const PointList &points)
        {
            a()->pushPoints(points);
        }

        void popPoints()
        {
            a()->popPoints();
        }

        void setPoints(const PointList &points)
        {
            a()->setPoints(points);
        }
    };

    // IModelData
    class ModelData : public Base::ModelData
    {
    public:
        Q_I_DERIVED__MODEL_DATA
        Q_I_DERIVED__MODEL_DATA__ROLE_FUNCTIONS

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

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IEntity:
            return Q_I_CREATE__AGGREGATE(Entity);
        case I::ISubEntity:
            Q_ASSERT(0); return 0;
        case I::IPoints:
            return Q_I_CREATE__AGGREGATE(Points);
        case I::IModelData:
            return Q_I_CREATE__AGGREGATE(ModelData);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

#endif // AC_CURVE_H
