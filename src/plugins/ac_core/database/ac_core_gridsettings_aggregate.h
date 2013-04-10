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

#ifndef AC_CORE_GRIDSETTINGS_AGGREGATE_H
#define AC_CORE_GRIDSETTINGS_AGGREGATE_H

#include <mi_core_object_aggregate.h>

namespace GridSettings {

class Aggregate : public Object::Aggregate
{
public:
    Aggregate(IAggregate *parent);
    ~Aggregate();

    IAggregate *timeGridLines;
    IAggregate *pitchGridLines;
    IAggregate *controlGridLines;
    enum { ItemCount = 3 };

    int snapEnabled : 1;
    int gridSnapEnabled : 1;
    qreal timeSnap;
    qreal pitchSnap;
    qreal controlSnap;
    enum { RoleCount = 5 };

    enum {
        ItemCountOffset = Object::Aggregate::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount,
        RoleCountOffset = Object::Aggregate::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

protected:
    void reset();
};

}

#endif
