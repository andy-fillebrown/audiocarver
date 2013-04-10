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

#ifndef AC_CORE_SCOREOBJECT_AGGREGATE_H
#define AC_CORE_SCOREOBJECT_AGGREGATE_H

#include <mi_core_object_aggregate.h>
#include "ac_core_global.h"

namespace ScoreObject {

class AC_CORE_EXPORT Aggregate : public Object::Aggregate
{
public:
    Aggregate(IAggregate *parent);
    ~Aggregate();

    IAggregate *pitchCurve;
    IAggregate *controlCurve;
    enum { ItemCount = 2 };

    qreal volume;
    enum { RoleCount = 1 };

    enum {
        ItemCountOffset = Object::Aggregate::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount,
        RoleCountOffset = Object::Aggregate::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };
};

}

#endif
