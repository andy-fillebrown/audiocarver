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

#ifndef AC_CORE_DATABASE_CURVE_AGGREGATE_H
#define AC_CORE_DATABASE_CURVE_AGGREGATE_H

#include <mi_core_database_object_aggregate.h>

#include "ac_core_global.h"

#include <QStack>

namespace Ac {
namespace Core {

class Point;
typedef QList<Point> PointList;

namespace Database {
namespace Curve {

typedef Mi::Core::Database::Object::Aggregate Aggregate_BaseClass;

class AC_CORE_EXPORT Aggregate : public Aggregate_BaseClass
{
    friend class ModelData;
    friend class Points;

    enum { RoleCount = 1 };

    QStack<PointList> _pointsStack;

protected:
    enum {
        RoleCountOffset = Aggregate_BaseClass::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    Aggregate()
    {}

    IAggregate *initialize();

    virtual void conformPoints() = 0;

    PointList &points()
    {
        return _pointsStack.top();
    }

    void pushPoints(const PointList &points);
    void popPoints();
    bool setPoints(const PointList &points);
};

}
}
}
}

#endif
