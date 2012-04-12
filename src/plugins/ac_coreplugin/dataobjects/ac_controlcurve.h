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

#ifndef AC_CONTROLCURVE_H
#define AC_CONTROLCURVE_H

#include "ac_curve.h"

#include <ac_graphicsparent.h>
#include <ac_scoreobject.h>

class AC_CORE_EXPORT ControlCurve : public Curve
{
    Q_I_DERIVED__AGGREGATOR(ControlCurve, Curve)

    Q_I_DERIVED__AGGREGATOR__ROLE_COUNT(1)
    int _controlId;

public:
    ControlCurve(int controlId = 0)
        :   _controlId(controlId)
    {}

    int controlId() const
    {
        return _controlId;
    }

    bool setControlId(int controlId)
    {
        if (_controlId == controlId)
            return false;
        Q_SCOPED_CHANGE(Ac::ControlIdRole)
        _controlId = controlId;
        return true;
    }

    // Curve

    ScoreObject *scoreObject() const
    {
        DataObject *parent = this->parent();
        return parent ? cast<ScoreObject>(parent->parent()) : 0;
    }

    void conformPoints()
    {
        PointList points = this->points();
        qSort(points);
        const int n = points.count();
        if (2 <= n) {
            points.first().pos = QPointF();
            points.last().pos.rx() = 1.0f;
            for (int i = 0;  i < n;  ++i) {
                Point &pt = points[i];
                pt.pos.rx() = qBound(qreal(0.0f), pt.pos.x(), qreal(1.0f));
                pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(1.0f));
            }
        }
        pointsStack().top() = points;
    }

    // GraphicsObject

    void updateGraphicsParent()
    {
        GraphicsParent *parent = graphicsParent();
        graphicsCurveItem()->setParentItem(parent ? parent->mainGraphicsItems()[Ac::ControlScene] : 0);
    }

    // IAggregator

    void *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::ISubEntity:
            return Q_I_CREATE__AGGREGATE(SubEntity);
        case I::IModelData:
            return Q_I_CREATE__AGGREGATE(ModelData);
        case I::IModelItem:
            return Q_I_CREATE__AGGREGATE(ModelItem);
        default:
            return Base::createAggregate(interfaceType);
        }
    }

protected:
    class SubEntity : public Base::SubEntity
    {
        Q_I_DERIVED__AGGREGATE(SubEntity)

        // ISubEntity

        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(a()->graphicsParent());
        }

        int sceneType() const
        {
            return Ac::ControlScene;
        }
    };

    class ModelData : public Base::ModelData
    {
        Q_I_DERIVED__MODEL_DATA
        Q_I_DERIVED__MODEL_DATA__ROLE_FUNCTIONS

        // IModelData

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::ControlIdRole:
                return a()->controlId();
            default:
                return Base::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::ControlIdRole:
                return a()->setControlId(qvariant_cast<int>(data));
            default:
                return Base::setVariant(data, role);
            }
        }
    };

    class ModelItem : public Base::ModelItem
    {
        Q_I_DERIVED__MODEL_ITEM
        Q_I_DERIVED__MODEL_ITEM__ITEM_TYPE(Ac::ControlCurveItem)
    };
};

#endif // AC_CONTROLCURVE_H
