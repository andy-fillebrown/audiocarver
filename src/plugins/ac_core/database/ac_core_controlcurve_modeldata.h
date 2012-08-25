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

#ifndef AC_CORE_CONTROLCURVE_MODELDATA_H
#define AC_CORE_CONTROLCURVE_MODELDATA_H

#include "ac_core_curve_modeldata.h"

namespace ControlCurve {

class ModelData : public Curve::ModelData
{
    int _controlType;
    enum { RoleCount = 1 };

public:
    enum {
        RoleCountOffset = Curve::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ModelData(IAggregate *aggregate)
        :   Curve::ModelData(aggregate)
        ,   _controlType(-1)
    {}

    IUnknown *initialize();

protected:
    void conformPoints();

    int controlType() const
    {
        return _controlType;
    }

    bool setControlType(int controlType);

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
