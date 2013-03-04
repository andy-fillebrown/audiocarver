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

#ifndef MI_CORE_OBJECT_MODELDATA_H
#define MI_CORE_OBJECT_MODELDATA_H

#include "mi_core_base_modeldata.h"

namespace Object {

class MI_CORE_EXPORT ModelData : public Base::ModelData
{
    QString _name;
    enum { RoleCount = 1 };

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = RoleCount
    };

    ModelData(IAggregate *aggregate)
        :   Base::ModelData(aggregate)
    {}

    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name);

    int roleCount() const
    {
        return RoleCount;
    }

    int roleAt(int i) const;

    int flags() const
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    QVariant getValue(int role) const;
    bool setValue(const QVariant &value, int role);
};

}

#endif
