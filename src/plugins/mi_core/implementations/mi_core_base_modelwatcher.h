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

#ifndef MI_CORE_BASE_MODELWATCHER_H
#define MI_CORE_BASE_MODELWATCHER_H

#include <imodelwatcher.h>
#include "mi_core_global.h"

class IAggregate;

namespace Base {

class MI_CORE_EXPORT ModelWatcher : public IModelWatcher
{
    IAggregate *_aggregate;

public:
    void *queryInterface(int interfaceType) const;

protected:
    ModelWatcher(IAggregate *aggregate);

    void initialize()
    {}

    void reset()
    {}

    void beginChangeData(IModelItem *item, int role)
    {}

    void endChangeData(IModelItem *item, int role)
    {}

    void beginInsertItem(IModelItem *list, int index)
    {}

    void endInsertItem(IModelItem *list, int index)
    {}

    void beginRemoveItem(IModelItem *list, int index)
    {}

    void endRemoveItem(IModelItem *list, int index)
    {}
};

}

#endif
