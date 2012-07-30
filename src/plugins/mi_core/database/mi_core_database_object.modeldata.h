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

class Aggregate;

class MI_CORE_EXPORT ModelData : public IModelData
{
    Aggregate *_aggregate;

protected:
    ModelData(IAggregate *aggregate);
    virtual IUnknown *initialize();

    Aggregate *aggregate() const
    {
        return _aggregate;
    }

    int roleCount() const;
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
