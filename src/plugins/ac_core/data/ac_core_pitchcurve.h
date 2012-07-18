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

#ifndef AC_CORE_PITCHCURVE_H
#define AC_CORE_PITCHCURVE_H

#include "ac_core_curve.h"

namespace Ac {
namespace Core {

class AC_CORE_EXPORT PitchCurve : public Curve
{
    friend class DataObjectFactory;

protected:
    PitchCurve()
    {}

    IAggregator *init();

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

    class AC_CORE_EXPORT ModelItem : public Curve::ModelItem
    {
        friend class PitchCurve;

    protected:
        ModelItem(PitchCurve *aggregator)
            :   Curve::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        int itemType() const
        {
            return Ac::PitchCurveItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (Ac::PitchCurveItem == itemType)
                return true;
            return Curve::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return Curve::createAggregate(interfaceType);
        }
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_PITCHCURVE_H
