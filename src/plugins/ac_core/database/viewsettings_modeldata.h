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

#ifndef VIEWSETTINGS_MODELDATA_H
#define VIEWSETTINGS_MODELDATA_H

#include <base/modeldata.h>

namespace ViewSettings {

class ModelData : public Base::ModelData
{
    qreal _timePosition;
    qreal _pitchPosition;
    qreal _controlPosition;
    qreal _timeScale;
    qreal _pitchScale;
    qreal _controlScale;
    enum { RoleCount = 6 };

public:
    enum {
        RoleCountOffset = Base::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ModelData(IAggregate *aggregate);
    IUnknown *initialize();

protected:
    qreal timePosition() const
    {
        return _timePosition;
    }

    bool setTimePosition(qreal position);

    qreal pitchPosition() const
    {
        return _pitchPosition;
    }

    bool setPitchPosition(qreal position);

    qreal controlPosition() const
    {
        return _controlPosition;
    }

    bool setControlPosition(qreal position);

    qreal timeScale() const
    {
        return _timeScale;
    }

    bool setTimeScale(qreal scale);

    qreal pitchScale() const
    {
        return _pitchScale;
    }

    bool setPitchScale(qreal scale);

    qreal controlScale() const
    {
        return _controlScale;
    }

    bool setControlScale(qreal scale);

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
