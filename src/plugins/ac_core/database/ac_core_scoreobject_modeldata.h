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

#ifndef AC_CORE_SCOREOBJECT_MODELDATA_H
#define AC_CORE_SCOREOBJECT_MODELDATA_H

#include <mi_core_object_modeldata.h>
#include "ac_core_global.h"

namespace ScoreObject {

class AC_CORE_EXPORT ModelData : public Object::ModelData
{
    qreal _volume;
    enum { RoleCount = 1 };

public:
    ModelData(IAggregate *aggregate);

protected:
    enum {
        RoleCountOffset = Object::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    bool setVolume(qreal volume);

    int roleCount() const;
    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(const QVariant &value, int role);
};

}

#endif
