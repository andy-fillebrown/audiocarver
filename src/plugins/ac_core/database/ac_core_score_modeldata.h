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

#ifndef AC_CORE_SCORE_MODELDATA_H
#define AC_CORE_SCORE_MODELDATA_H

#include "ac_core_scoreobject_modeldata.h"

namespace Score {

class ModelData : public ScoreObject::ModelData
{
    qreal _length;
    qreal _startTime;
    enum { RoleCount = 2 };

public:
    enum {
        RoleCountOffset = ScoreObject::ModelData::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ModelData(IAggregate *aggregate);
    IUnknown *initialize();

protected:
    qreal length() const
    {
        return _length;
    }

    bool setLength(qreal length);

    qreal startTime() const
    {
        return _startTime;
    }

    bool setStartTime(qreal time);

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
