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

#ifndef AC_CORE_CONTROLCURVE_H
#define AC_CORE_CONTROLCURVE_H

#include "ac_core_curve.h"

namespace Ac {
namespace Core {

class AC_CORE_EXPORT ControlCurve : public Curve
{
    friend class DataObjectFactory;

    enum { RoleCount = 1 };

    int _controlType;

protected:
    enum {
        RoleCountOffset = DataObject::TotalRoleCount,
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
        friend class ControlCurve;

        ControlCurve *a() const
        {
            return static_cast<ControlCurve*>(DataObject::ModelData::a());
        }

    protected:
        ModelData(ControlCurve *aggregator)
            :   Curve::ModelData(aggregator)
        {}

        IAggregate *init();

        // IModelData
        int roleCount() const
        {
            return TotalRoleCount;
        }

        int roleAt(int i) const
        {
            switch (i - RoleCountOffset) {
            case 0:
                return ControlTypeRole;
            default:
                return Curve::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case ControlTypeRole:
                return a()->controlType();
            default:
                return Curve::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case ControlTypeRole:
                return a()->setControlType(qvariant_cast<int>(data));
            default:
                return Curve::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public Curve::ModelItem
    {
        friend class ControlCurve;

    protected:
        ModelItem(ControlCurve *aggregator)
            :   Curve::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        int itemType() const
        {
            return ControlCurveItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (ControlCurveItem == itemType)
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

} // namespace Core
} // namespace Ac

#endif // AC_CORE_CONTROLCURVE_H
