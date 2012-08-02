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

#ifndef AC_CORE_CURVE_MODELDATA_H
#define AC_CORE_CURVE_MODELDATA_H

#include <mi_core_base_modeldata.h>

class Point;
typedef QList<Point> PointList;

namespace Curve {

class ModelData : public Base::ModelData
{
    PointList _points;
    enum { RoleCount = 1 };

protected:
    enum {
        RoleCountOffset = Base::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ModelData(IAggregate *aggregate);
    IUnknown *initialize();

    PointList &points()
    {
        return _points;
    }

    bool setPoints(const PointList &points);

    virtual void conformPoints() = 0;

    int roleCount() const
    {
        return RoleCount;
    }

    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(const QVariant &value, int role);
};

}

#endif
