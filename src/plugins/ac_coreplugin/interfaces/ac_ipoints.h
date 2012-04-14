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

#ifndef AC_IPOINTS_H
#define AC_IPOINTS_H

#include "mi_iaggregate.h"

#include <ac_namespace.h>

class Point;

typedef QList<Point> PointList;

class IPoints : public IAggregate
{
public:
    Q_I_DERIVED__UNKNOWN__INTERFACE_TYPE(IPoints, IAggregate)

    virtual const PointList &points() const = 0;
    virtual void pushPoints(const PointList &points) = 0;
    virtual void popPoints() = 0;
    virtual void setPoints(const PointList &points) = 0;

    void pushPoints()
    {
        pushPoints(points());
    }

    void setPoints()
    {
        setPoints(points());
    }
};

#endif // AC_IPOINTS_H
