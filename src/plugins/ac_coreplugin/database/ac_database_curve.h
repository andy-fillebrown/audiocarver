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

#ifndef AC_DATABASE_CURVE_H
#define AC_DATABASE_CURVE_H

#include "mi_database_object.h"
#include "ac_ipoints.h"

#include <ac_point.h>

#include <QStack>

namespace Database {

class AC_CORE_EXPORT Curve : public Object
{
    QStack<PointList> _pointsStack;
    enum { RoleCount = 1 };

protected:
    enum {
        RoleCountOffset = Object::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    Curve()
    {}

    IAggregator *init();

    virtual void conformPoints() = 0;

public:
    PointList &points()
    {
        return _pointsStack.top();
    }

    void pushPoints(const PointList &points);
    void popPoints();
    bool setPoints(const PointList &points);

protected:
    class AC_CORE_EXPORT Points : public IPoints
    {
        Curve *_aggregator;

    public:
        Points(Curve *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

    protected:
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

    class AC_CORE_EXPORT ModelData : public Object::ModelData
    {
        Curve *a() const
        {
            return cast<Curve>(Object::ModelData::a());
        }

    public:
        ModelData(Curve *aggregator)
            :   Object::ModelData(aggregator)
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
                return Ac::PointsRole;
            default:
                return Object::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::PointsRole:
                return QVariant::fromValue(a()->points());
            default:
                return Object::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::PointsRole:
                return a()->setPoints(qvariant_cast<PointList>(data));
            default:
                return Object::ModelData::setVariant(data, role);
            }
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
            return Object::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_CURVE_H
