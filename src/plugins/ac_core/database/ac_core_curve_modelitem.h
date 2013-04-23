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

#ifndef AC_CORE_CURVE_MODELITEM_H
#define AC_CORE_CURVE_MODELITEM_H

#include <mi_core_object_modelitem.h>
#include "ac_core_point.h"

namespace Curve {

class AC_CORE_EXPORT ModelItem : public Object::ModelItem
{
    PointList _points;
    enum { RoleCount = 1 };

public:
    ModelItem(IAggregate *aggregate)
        :   Object::ModelItem(aggregate)
    {}

protected:
    PointList &points()
    {
        return _points;
    }

    enum {
        RoleCountOffset = Object::ModelItem::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    bool isTypeOfItem(int itemType) const;

    int roleCount() const
    {
        return TotalRoleCount;
    }

    int roleAt(int i) const;
    QVariant getValue(int role) const;
    bool setValue(int role, const QVariant &value);

    virtual void conformPoints() = 0;
};

}

#endif
