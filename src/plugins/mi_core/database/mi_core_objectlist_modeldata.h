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

#ifndef MI_CORE_OBJECTLIST_MODELDATA_H
#define MI_CORE_OBJECTLIST_MODELDATA_H

#include "mi_core_base_modeldata.h"

namespace ObjectList {

class MI_CORE_EXPORT ModelData : public Base::ModelData
{
    enum { RoleCount = 0 };

public:
    ModelData(IAggregate *aggregate)
        :   Base::ModelData(aggregate)
    {}

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = 0
    };

    int roleCount() const
    {
        return RoleCount;
    }

    int roleAt(int i) const
    {
        return 0;
    }

    int flags() const
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    QVariant getValue(int role) const;

    bool setValue(const QVariant &value, int role)
    {
        Q_ASSERT(0);
        return false;
    }
};

}

#endif
