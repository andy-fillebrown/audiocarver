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

#ifndef MI_CORE_DATABASE_OBJECT_MODELITEM_H
#define MI_CORE_DATABASE_OBJECT_MODELITEM_H

#include "mi_imodelitem.h"

class IAggregate;

namespace Mi {
namespace Core {
namespace Database {
namespace Object {

class MI_CORE_EXPORT ModelItem : public IModelItem
{
    IAggregate *_aggregate;
    IModelItem *_parent;

protected:
    ModelItem(IAggregate *aggregate)
        :   _aggregate(aggregate)
        ,   _parent(0)
    {}

    virtual IUnknown *initialize();

    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    int itemType() const
    {
        return UnknownItem;
    }

    bool isTypeOfItem(int itemType) const
    {
        return UnknownItem == itemType;
    }

    IModelItem *parent() const
    {
        return _parent;
    }

    void setParent(IModelItem *parent);
    IModelItemList *list() const;

    int count() const
    {
        return 0;
    }

    int indexOf(IModelItem *item) const
    {
        Q_ASSERT(false);
        return -1;
    }

    IModelItem *at(int i) const
    {
        Q_ASSERT(false);
        return 0;
    }

    IModelItem *findItem(int itemType) const
    {
        return 0;
    }

    IModelItemList *findList(int listType) const
    {
        return 0;
    }
};

}
}
}
}

#endif
