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

#ifndef AC_CORE_VIEWSETTINGS_MODELDATA_H
#define AC_CORE_VIEWSETTINGS_MODELDATA_H

#include <mi_core_object_modeldata.h>

namespace ViewSettings {

class ModelData : public Object::ModelData
{
    qreal _timePosition;
    qreal _pitchPosition;
    qreal _controlPosition;
    qreal _timeScale;
    qreal _pitchScale;
    qreal _controlScale;
    enum { RoleCount = 6 };

public:
    ModelData(IAggregate *aggregate);

protected:
    enum {
        RoleCountOffset = Object::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    bool setTimePosition(qreal position);
    bool setPitchPosition(qreal position);
    bool setControlPosition(qreal position);
    bool setTimeScale(qreal scale);
    bool setPitchScale(qreal scale);
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
