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

#ifndef MI_CORE_DATABASE_OBJECTLIST_MODELITEMLIST_H
#define MI_CORE_DATABASE_OBJECTLIST_MODELITEMLIST_H

#include "mi_imodelitemlist.h"

class IAggregate;

namespace Mi {
namespace Core {
namespace Database {
namespace ObjectList {

class Aggregate;

class MI_CORE_EXPORT ModelItemList : public IModelItemList
{
    friend class Aggregate;

    Aggregate *_aggregate;

protected:
    ModelItemList(IAggregate *aggregate);
    virtual IUnknown *initialize();

    Aggregate *aggregate() const
    {
        return _aggregate;
    }

    int itemType() const
    {
        return ListItem;
    }

    bool isTypeOfItem(int itemType) const
    {
        return ListItem == itemType;
    }

    IModelItem *parent() const;
    void setParent(IModelItem *parent);

    IModelItemList *list() const
    {
        return 0;
    }

    int count() const;
    int indexOf(const IModelItem *item) const;
    IModelItem *at(int i) const;

    IModelItem *findItem(int itemType) const
    {
        Q_ASSERT(0);
        return 0;
    }

    IModelItemList *findList(int listType) const
    {
        Q_ASSERT(0);
        return 0;
    }

    int listType() const;
    bool contains(const QString &name) const;
    void insert(int i, IModelItem *item);
    void removeAt(int i);
    void clear();
};

}
}
}
}

#endif
