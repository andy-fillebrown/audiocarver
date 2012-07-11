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

#ifndef AC_CORE_CURVE_H
#define AC_CORE_CURVE_H

#include "mi_core_dataobject.h"

#include "ac_ipoints.h"

#include <ac_core_point.h>

#include <QStack>

namespace Ac {
namespace Core {

class AC_CORE_EXPORT Curve : public Mi::Core::DataObject
{
    enum { RoleCount = 1 };

    QStack<PointList> _pointsStack;

protected:
    enum {
        RoleCountOffset = DataObject::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    Curve()
    {}

    IAggregator *init();

    virtual void conformPoints() = 0;

    PointList &points()
    {
        return _pointsStack.top();
    }

    void pushPoints(const PointList &points);
    void popPoints();
    bool setPoints(const PointList &points);

    class AC_CORE_EXPORT Points : public IPoints
    {
        friend class Curve;

        Curve *_aggregator;

    protected:
        Points(Curve *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

        Curve *a() const
        {
            return _aggregator;
        }

        // IPoints
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

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    class AC_CORE_EXPORT ModelData : public DataObject::ModelData
    {
        friend class Curve;

        Curve *a() const
        {
            return static_cast<Curve*>(DataObject::ModelData::a());
        }

    protected:
        ModelData(Curve *aggregator)
            :   DataObject::ModelData(aggregator)
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
                return Ac::PointsRole;
            default:
                return DataObject::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::PointsRole:
                return QVariant::fromValue(a()->points());
            default:
                return DataObject::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::PointsRole:
                return a()->setPoints(qvariant_cast<PointList>(data));
            default:
                return DataObject::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public DataObject::ModelItem
    {
    protected:
        ModelItem(Curve *aggregator)
            :   DataObject::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        bool isTypeOfItem(int itemType) const
        {
            if (Ac::CurveItem == itemType)
                return true;
            return DataObject::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IPoints:
            return appendAggregate((new Points(this))->init());
        case I::IModelData:
            return appendAggregate((new ModelData(this))->init());
        default:
            return DataObject::createAggregate(interfaceType);
        }
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_CURVE_H
