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

#ifndef AC_CORE_DATABASE_SCOREOBJECT_AGGREGATE_H
#define AC_CORE_DATABASE_SCOREOBJECT_AGGREGATE_H

#include <mi_core_database_object_aggregate.h>

#include "ac_core_global.h"

namespace Ac {
namespace Core {
namespace Database {
namespace ScoreObject {

typedef Mi::Core::Database::Object::Aggregate Aggregate_BaseClass;

class AC_CORE_EXPORT Aggregate : public Aggregate_BaseClass
{
    friend class ModelData;
    friend class ModelItem;

    enum { RoleCount = 1 };
    enum { ItemCount = 2 };

    qreal _volume;

    IAggregate *_pitchCurve;
    IAggregate *_controlCurves;

protected:
    enum {
        RoleCountOffset = Aggregate_BaseClass::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount,
        ItemCountOffset = Aggregate_BaseClass::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    Aggregate();
    IAggregate *initialize();
    ~Aggregate();

    qreal volume() const
    {
        return _volume;
    }

    bool setVolume(qreal volume);

    IAggregate *pitchCurve() const
    {
        return _pitchCurve;
    }

    IAggregate *controlCurves() const
    {
        return _controlCurves;
    }

    void clear();
};

}
}
}
}

#endif
