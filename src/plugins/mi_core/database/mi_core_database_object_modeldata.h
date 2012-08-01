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

#ifndef MI_CORE_DATABASE_OBJECT_MODELDATA_H
#define MI_CORE_DATABASE_OBJECT_MODELDATA_H

#include "mi_imodeldata.h"

class IAggregate;

namespace Mi {
namespace Core {
namespace Database {
namespace Object {

class MI_CORE_EXPORT ModelData : public IModelData
{
    IAggregate *_aggregate;

    QString _name;

public:
    enum { RoleCount = 1 };

protected:
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

    Qt::ItemFlags flags() const
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    QVariant getValue(int role) const;
    bool setValue(const QVariant &value, int role);
};

}
}
}
}

#endif
