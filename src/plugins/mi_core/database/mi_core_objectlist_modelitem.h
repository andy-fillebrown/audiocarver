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

#ifndef MI_CORE_OBJECTLIST_MODELITEM_H
#define MI_CORE_OBJECTLIST_MODELITEM_H

#include "mi_core_base_modelitemlist.h"
#include <QList>

namespace ObjectList {

class MI_CORE_EXPORT ModelItem : public Base::ModelItemList
{
    IModelItem *_parent;
    const int _listType;
    QList<IModelItem*> _items;

public:
    ModelItem(IAggregate *aggregate, int listType)
        :   Base::ModelItemList(aggregate)
        ,   _parent(0)
        ,   _listType(listType)
    {}

protected:
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

    int indexOf(const IModelItem *item) const
    {
        return _items.indexOf(const_cast<IModelItem*>(item));
    }

    IModelItem *at(int i) const
    {
        if (i < count())
            return _items.at(i);
        return 0;
    }

    IModelItem *findItem(int itemType) const
    {
        Q_ASSERT(0);
        return 0;
    }

    IModelItemList *findList(int listType) const
    {
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
