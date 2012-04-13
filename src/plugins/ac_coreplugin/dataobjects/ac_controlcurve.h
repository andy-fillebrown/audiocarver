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

protected:
    int controlId() const
    {
        return _controlId;
    }

    bool setControlId(int controlId)
    {
        if (_controlId == controlId)
            return false;
        Q_DATA_CHANGE((Ac::ControlIdRole))
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
        PointList &pts = points();
        qSort(pts);
        const int n = pts.count();
        if (2 <= n) {
            pts.first().pos = QPointF();
            pts.last().pos.rx() = 1.0f;
            for (int i = 0;  i < n;  ++i) {
                Point &pt = pts[i];
                pt.pos.rx() = qBound(qreal(0.0f), pt.pos.x(), qreal(1.0f));
                pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(1.0f));
            }
        }
    }

    // GraphicsObject
    void updateGraphicsParent()
    {
        GraphicsParent *parent = graphicsParent();
        graphicsCurveItem()->setParentItem(parent ? parent->mainGraphicsItems()[Ac::ControlScene] : 0);
    }

    // ISubEntity
    class SubEntity : public Base::SubEntity
    {
        Q_I_DERIVED__AGGREGATE(SubEntity)

        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(a()->graphicsParent());
        }

        int sceneType() const
        {
            return Ac::ControlScene;
        }
    };

    // IModelData
    class ModelData : public Base::ModelData
    {
        Q_I_DERIVED__MODEL_DATA
        Q_I_DERIVED__MODEL_DATA__ROLE_FUNCTIONS

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

    // IModelItem
    class ModelItem : public Base::ModelItem
    {
        Q_I_DERIVED__MODEL_ITEM
        Q_I_DERIVED__MODEL_ITEM__ITEM_TYPE(Ac::ControlCurveItem)
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
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
};

#endif // AC_CONTROLCURVE_H
