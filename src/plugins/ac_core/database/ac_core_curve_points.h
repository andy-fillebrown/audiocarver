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

#ifndef AC_CORE_DATABASE_CURVE_POINTS_H
#define AC_CORE_DATABASE_CURVE_POINTS_H

#include "ac_ipoints.h"

namespace Ac {
namespace Core {
namespace Database {
namespace Curve {

class Aggregate;

class AC_CORE_EXPORT Points : public IPoints
{
    Aggregate *_aggregate;

protected:
    Aggregate *aggregate() const
    {
        return _aggregate;
    }

    Points(IAggregate *aggregate);
    virtual IUnknown *initialize();

    const PointList &points() const;
    void pushPoints(const PointList &points);
    void popPoints();
    void setPoints(const PointList &points);
};

}
}
}
}

#endif
