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
    GraphicsCurveItem *_graphicsCurveItem;

    QStack<PointList> _pointsStack;
    Q_I_DERIVED__AGGREGATOR__ROLE_COUNT(1)

protected:
    Curve()
        :   _graphicsCurveItem(0)
    {}

    ~Curve();

    virtual ScoreObject *scoreObject() const = 0;
    virtual void conformPoints() = 0;

    GraphicsCurveItem *graphicsCurveItem() const
    {
        return _graphicsCurveItem;
    }

    PointList &points()
    {
        return _pointsStack.top();
    }

    void pushPoints(const PointList &points);
    void popPoints();
    bool setPoints(const PointList &points);

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
            return Q_I_NEW__AGGREGATE(Entity);
        case I::ISubEntity:
            Q_ASSERT(0); return 0;
        case I::IPoints:
            return Q_I_NEW__AGGREGATE(Points);
        case I::IModelData:
            return Q_I_NEW__AGGREGATE(ModelData);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

#endif // AC_CURVE_H
