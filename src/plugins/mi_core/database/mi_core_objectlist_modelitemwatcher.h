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

#ifndef MI_CORE_OBJECTLIST_MODELITEMWATCHER_H
#define MI_CORE_OBJECTLIST_MODELITEMWATCHER_H

#include <imodelitemwatcher.h>
#include "mi_core_global.h"

class IAggregate;

namespace ObjectList {

class MI_CORE_EXPORT ModelItemWatcher : public IModelItemWatcher
{
    IAggregate *_aggregate;

public:
    ModelItemWatcher(IAggregate *aggregate)
        :   _aggregate(aggregate)
    {}

    virtual IUnknown *initialize();
    void *queryInterface(int interfaceType) const;

protected:
    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    void beginInsertItem(const IModelItem *parent, int index);
    void endInsertItem(const IModelItem *parent, int index);
    void beginRemoveItem(const IModelItem *parent, int index);
    void endRemoveItem(const IModelItem *parent, int index);
};

}

#endif
