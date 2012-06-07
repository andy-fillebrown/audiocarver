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

    enum { RoleCount = 1 };

    int _controlType;

protected:
    enum {
        RoleCountOffset = Object::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ControlCurve()
        :   _controlType(-1)
    {}

    IAggregator *init();

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

    class AC_CORE_EXPORT ModelData : public Curve::ModelData
    {
        ControlCurve *a() const
        {
            return cast<ControlCurve>(Object::ModelData::a());
        }

    public:
        ModelData(ControlCurve *aggregator)
            :   Curve::ModelData(aggregator)
        {}

        IAggregate *init();

    protected:
        // IModelData
        int roleCount() const
        {
            return TotalRoleCount;
        }

        int roleAt(int i) const
        {
            Q_ASSERT(0 <= i);
            switch (i - RoleCountOffset) {
            case 0:
                return Ac::ControlTypeRole;
            default:
                return Curve::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::ControlTypeRole:
                return a()->controlType();
            default:
                return Curve::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::ControlTypeRole:
                return a()->setControlType(qvariant_cast<int>(data));
            default:
                return Curve::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public Curve::ModelItem
    {
    public:
        ModelItem(ControlCurve *aggregator)
            :   Curve::ModelItem(aggregator)
        {}

        IAggregate *init();

    protected:
        // IModelItem
        int itemType() const
        {
            return Ac::ControlCurveItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (Ac::ControlCurveItem == itemType)
                return true;
            return Curve::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelData:
            return appendAggregate((new ModelData(this))->init());
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return Curve::createAggregate(interfaceType);
        }
    }
};

} // Database

#endif // AC_DATABASE_CONTROLCURVE_H