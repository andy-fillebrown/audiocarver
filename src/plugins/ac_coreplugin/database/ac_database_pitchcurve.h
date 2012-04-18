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

#ifndef AC_DATABASE_PITCHCURVE_H
#define AC_DATABASE_PITCHCURVE_H

#include "ac_database_curve.h"

namespace Database {

class AC_CORE_EXPORT PitchCurve : public Curve
{
    friend class ObjectFactory;

    Q_IAGGREGATOR_DERIVED(PitchCurve, Curve)

protected:
    PitchCurve()
    {}

    // Curve
    void conformPoints()
    {
        PointList &pts = points();
        qSort(pts);
        const int n = pts.count();
        for (int i = 0;  i < n;  ++i) {
            Point &pt = pts[i];
            pt.pos.rx() = qMax(qreal(0.0f), pt.pos.x());
            pt.pos.ry() = qBound(qreal(0.0f), pt.pos.y(), qreal(127.0f));
        }
    }

    // IModelItem
    class AC_CORE_EXPORT ModelItem : public Base::ModelItem
    {
        Q_IMODELITEM_DERIVED
        Q_IMODELITEM_DERIVED__ITEMTYPE(Ac::PitchCurveItem)
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelItem:
            return Q_NEW_AGGREGATE(ModelItem);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_PITCHCURVE_H
