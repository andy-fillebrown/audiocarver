/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_CORE_CONTROLCURVE_MODELDATA_H
#define AC_CORE_CONTROLCURVE_MODELDATA_H

#include "ac_core_curve_modeldata.h"

namespace ControlCurve {

class ModelData : public Curve::ModelData
{
    int _controlType;
    enum { RoleCount = 1 };

public:
    ModelData(IAggregate *aggregate)
        :   Curve::ModelData(aggregate)
        ,   _controlType(-1)
    {}

protected:
    enum {
        RoleCountOffset = Curve::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    bool setControlType(int controlType);

    void conformPoints();

    int roleCount() const
    {
        return TotalRoleCount;
    }

    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(const QVariant &value, int role);
};

}

#endif
