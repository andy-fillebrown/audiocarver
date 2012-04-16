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

#ifndef AC_ABSTRACTCURVEDATAOBJECT_H
#define AC_ABSTRACTCURVEDATAOBJECT_H

#include "mi_dataobject.h"
#include "ac_ipoints.h"

#include <ac_point.h>

#include <QStack>

class AC_CORE_EXPORT AbstractCurveDataObject : public DataObject
{
    Q_IAGGREGATOR_DERIVED(AbstractCurveDataObject, DataObject)

    QStack<PointList> _pointsStack;
    Q_IAGGREGATOR_DERIVED__ROLECOUNT(1)

protected:
    AbstractCurveDataObject()
    {}

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
    // IPoints
    class Points : public IPoints
    {
        Q_IAGGREGATE_BASE(Points)

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
        Q_IMODELDATA_DERIVED
        Q_IMODELDATA_DERIVED__ROLE_FUNCTIONS

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
        case I::IPoints:
            return Q_NEW_AGGREGATE(Points);
        case I::IModelData:
            return Q_NEW_AGGREGATE(ModelData);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

#endif // AC_ABSTRACTCURVEDATAOBJECT_H
