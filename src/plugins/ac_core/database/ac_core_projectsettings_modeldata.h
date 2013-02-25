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

#ifndef AC_CORE_PROJECTSETTINGS_MODELDATA_H
#define AC_CORE_PROJECTSETTINGS_MODELDATA_H

#include <mi_core_object_modeldata.h>

namespace ProjectSettings {

class ModelData : public Object::ModelData
{
    int _sampleRate;
    int _controlRate;
    int _curveRate;
    enum { RoleCount = 3 };

public:
    ModelData(IAggregate *aggregate);

protected:
    enum {
        RoleCountOffset = Object::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    bool setSampleRate(int rate);
    bool setControlRate(int rate);
    bool setCurveRate(int rate);

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
