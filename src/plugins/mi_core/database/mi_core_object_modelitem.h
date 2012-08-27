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

#ifndef MI_CORE_OBJECT_MODELITEM_H
#define MI_CORE_OBJECT_MODELITEM_H

#include <imodelitem.h>
#include "mi_core_global.h"

class IAggregate;

namespace Object {

class MI_CORE_EXPORT ModelItem : public IModelItem
{
    IAggregate *_aggregate;
    IModelItem *_parent;

    enum { ItemCount = 0 };

public:
    void *queryInterface(int interfaceType) const;

protected:
    enum {
        ItemCountOffset = 0,
        TotalItemCount = ItemCount
    };

    ModelItem(IAggregate *aggregate)
        :   _aggregate(aggregate)
        ,   _parent(0)
    {}

    virtual IUnknown *initialize();

    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    int itemType() const;

    bool isTypeOfItem(int itemType) const
    {
        return false;
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

    int indexOf(const IModelItem *item) const
    {
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
        IModelItemList *list = 0;
        const int count = this->count();
        for (int i = 0;  i < count;  ++i) {
            list = at(i)->findList(listType);
            if (list)
                return list;
        }
        Q_ASSERT(0);
        return 0;
    }

    void reset()
    {
        const int item_count = count();
        for (int i = 0;  i < item_count;  ++i)
            at(i)->reset();
    }
};

}

#endif
