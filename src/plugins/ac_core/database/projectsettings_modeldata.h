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

#ifndef PROJECTSETTINGS_MODELDATA_H
#define PROJECTSETTINGS_MODELDATA_H

#include <base/modeldata.h>

namespace ProjectSettings {

class ModelData : public Base::ModelData
{
    int _sampleRate;
    int _controlRate;
    int _curveRate;
    enum { RoleCount = 3 };

public:
    enum {
        RoleCountOffset = Base::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ModelData(IAggregate *aggregate);
    IUnknown *initialize();

protected:
    int sampleRate() const
    {
        return _sampleRate;
    }

    bool setSampleRate(int rate);

    int controlRate() const
    {
        return _controlRate;
    }

    bool setControlRate(int rate);

    int curveRate() const
    {
        return _curveRate;
    }

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
