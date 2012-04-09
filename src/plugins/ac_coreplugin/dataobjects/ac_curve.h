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

class AC_CORE_EXPORT Curve : public GraphicsObject
{
    QScopedPointer<GraphicsCurveItem> _graphicsCurveItem;
    QStack<PointList> _pointsStack;

protected:
    Curve();
    ~Curve();

    GraphicsCurveItem *graphicsCurveItem() const
    {
        return qGetPtrHelper(_graphicsCurveItem);
    }

    QStack<PointList> &pointsStack()
    {
        return _pointsStack;
    }

    bool setPoints(const PointList &points);
    virtual void conformPoints() = 0;
    void updateGraphicsItems();

    virtual ScoreObject *scoreObject() const = 0;
    void setColor(const QColor &color);

    // GraphicsObject

    GraphicsParent *graphicsParent() const;

    // IAggregator

    void *createAggregate(int interface)
    {
        switch (interface) {
        case Ac::EntityInterface:
            return appendAggregate(new Entity(this));
        default:
            return GraphicsObject::createAggregate(interface);
        }
    }

    // ------------------------------------------------------------------------

    class Entity : public IEntity
    {
        Curve *_aggregator;

    public:
        Entity(Curve *aggregator)
            :   _aggregator(aggregator)
        {}

        Curve *dataObject() const
        {
            return _aggregator;
        }

        // IEntity

        void highlight();
        void unhighlight();
        bool intersects(const QRectF &rect) const;
        bool isVisible() const;

        // IAggregate

        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    // ------------------------------------------------------------------------

    class SubEntity : public ISubEntity
    {
        Curve *_aggregator;

    public:
        SubEntity(Curve *aggregator)
            :   _aggregator(aggregator)
        {}

        // ISubEntity

        bool isCurve() const
        {
            return true;
        }

        // IAggregate

        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    // ------------------------------------------------------------------------

    class Points : public IPoints
    {
        Curve *_aggregator;

    public:
        Points(Curve *aggregator)
            :   _aggregator(aggregator)
        {}

        Curve *dataObject() const
        {
            return qGetPtrHelper(_aggregator);
        }

        const PointList &points() const
        {
            return dataObject()->pointsStack().top();
        }

        void pushPoints(const PointList &points)
        {
            Curve *data_object = dataObject();
            data_object->pointsStack().push(points);
            data_object->updateGraphicsItems();
        }

        void popPoints()
        {
            Curve *data_object = dataObject();
            data_object->pointsStack().pop();
            data_object->updateGraphicsItems();
        }

        void setPoints(const PointList &points)
        {
            dataObject()->setPoints(points);
        }
    };

    // ------------------------------------------------------------------------

    class ModelData : public GraphicsObject::ModelData
    {
    public:
        ModelData(Curve *aggregator)
            :   GraphicsObject::ModelData(aggregator)
        {}

        Curve *dataObject() const
        {
            return cast<Curve>(GraphicsObject::ModelData::dataObject());
        }

        int roleCount() const
        {
            return GraphicsObject::ModelData::roleCount() + 1;
        }

        int roleAt(int i) const
        {
            if (GraphicsObject::ModelData::roleCount() == i)
                return Ac::PointsRole;
            return GraphicsObject::ModelData::roleAt(i);
        }

        QVariant get(int role) const;
        bool set(const QVariant &data, int role);
    };

    typedef GraphicsObject::ModelItem ModelItem;
};

#endif // AC_CURVE_H
