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

#ifndef AC_DATABASE_CONTROLCURVE_H
#define AC_DATABASE_CONTROLCURVE_H

#include "ac_database_curve.h"

namespace Database {

class AC_CORE_EXPORT ControlCurve : public Curve
{
    friend class ObjectFactory;

    Q_IAGGREGATOR_DERIVED(ControlCurve, Curve)

    int _controlType;
    Q_IAGGREGATOR_DERIVED__ROLECOUNT(1)

protected:
    ControlCurve()
        :   _controlType(-1)
    {}

    int controlType() const
    {
        return _controlType;
    }

    bool setControlType(int controlType);

    // Curve
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

    // IModelData
    class AC_CORE_EXPORT ModelData : public Base::ModelData
    {
        Q_IMODELDATA_DERIVED
        Q_IMODELDATA_DERIVED__ROLE_FUNCTIONS

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::ControlTypeRole:
                return a()->controlType();
            default:
                return Base::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::ControlTypeRole:
                return a()->setControlType(qvariant_cast<int>(data));
            default:
                return Base::setVariant(data, role);
            }
        }
    };

    // IModelItem
    class AC_CORE_EXPORT ModelItem : public Base::ModelItem
    {
        Q_IMODELITEM_DERIVED
        Q_IMODELITEM_DERIVED__ITEMTYPE(Ac::ControlCurveItem)
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelData:
            return Q_NEW_AGGREGATE(ModelData);
        case I::IModelItem:
            return Q_NEW_AGGREGATE(ModelItem);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

} // Database

#endif // AC_DATABASE_CONTROLCURVE_H
