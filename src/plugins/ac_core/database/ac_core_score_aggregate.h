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

#ifndef AC_CORE_SCORE_AGGREGATE_H
#define AC_CORE_SCORE_AGGREGATE_H

#include <mi_core_object_aggregate.h>
#include "ac_core_global.h"

namespace Score {

class AC_CORE_EXPORT Aggregate : public Object::Aggregate
{
public:
    Aggregate(IAggregate *aggregate)
        :   Object::Aggregate(aggregate)
        ,   tracks(0)
        ,   gridSettings(0)
        ,   projectSettings(0)
        ,   viewSettings(0)
    {}

    ~Aggregate();

    IAggregate *tracks;
    IAggregate *gridSettings;
    IAggregate *projectSettings;
    IAggregate *viewSettings;
    enum { ItemCount = 4 };

    qreal length;
    qreal startTime;
    enum { RoleCount = 2 };

    enum {
        ItemCountOffset = Object::Aggregate::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount,
        RoleCountOffset = Object::Aggregate::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

protected:
    void initialize();
    void reset();
};

}

#endif
