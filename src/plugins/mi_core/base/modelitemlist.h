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

#ifndef BASE_MODELITEMLIST_H
#define BASE_MODELITEMLIST_H

#include <interfaces/imodelitemlist.h>
#include "mi_core_global.h"
#include <QList>

class IAggregate;

namespace Base {

class Aggregate;

class MI_CORE_EXPORT ModelItemList : public IModelItemList
{
    IAggregate *_aggregate;
    IModelItem *_parent;
    const int _listType;
    QList<IModelItem*> _items;

public:
    ModelItemList(IAggregate *aggregate, int listType)
        :   _aggregate(aggregate)
        ,   _parent(0)
        ,   _listType(listType)
    {}

    virtual IUnknown *initialize();

    void *queryInterface(int interfaceType) const;

protected:
    IAggregate *aggregate() const
    {
        return _aggregate;
    }

    int itemType() const;
    bool isTypeOfItem(int itemType) const;

    IModelItem *parent() const
    {
        return _parent;
    }

    void setParent(IModelItem *parent);

    IModelItemList *list() const
    {
        return 0;
    }

    int count() const
    {
        return _items.count();
    }

    int indexOf(IModelItem *item) const
    {
        return _items.indexOf(item);
    }

    IModelItem *at(int i) const
    {
        return _items.at(i);
    }

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

    int listType() const
    {
        return _listType;
    }

    bool contains(const QString &name) const;
    void insert(int i, IModelItem *item);
    void removeAt(int i);
    void reset();
};

}

#endif
