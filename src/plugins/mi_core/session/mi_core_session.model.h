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

#ifndef MI_CORE_SESSION_MODEL_H
#define MI_CORE_SESSION_MODEL_H

#include "mi_imodel.h"

class IAggregate;

namespace Mi {
namespace Core {
namespace Session {

class Aggregate;

class MI_CORE_EXPORT Model : public IModel
{
    Aggregate *_aggregate;

public:
    Model(IAggregate *aggregate);
    ~Model();
    virtual IUnknown *initialize();

    Aggregate *aggregate() const
    {
        return _aggregate;
    }

    IModelItem *rootItem() const
    {
        return 0;
    }

    void *queryInterface(int interfaceType) const;
};

}
}
}

#endif
