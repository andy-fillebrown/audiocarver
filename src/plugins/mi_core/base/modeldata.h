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

#ifndef BASE_MODELDATA_H
#define BASE_MODELDATA_H

#include <interfaces/imodeldata.h>
#include "mi_core_global.h"

class IAggregate;

namespace Base {

class MI_CORE_EXPORT ModelData : public IModelData
{
    IAggregate *_aggregate;

    QString _name;
    enum { RoleCount = 1 };

public:
    void *queryInterface(int interfaceType) const;

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = RoleCount
    };

    ModelData(IAggregate *aggregate)
        :   _aggregate(aggregate)
    {}

    virtual IUnknown *initialize();

    IAggregate *aggregate() const
    {
        return _aggregate;
    }

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
