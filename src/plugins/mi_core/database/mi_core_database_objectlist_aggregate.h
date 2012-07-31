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

#ifndef MI_CORE_DATABASE_OBJECTLIST_AGGREGATE_H
#define MI_CORE_DATABASE_OBJECTLIST_AGGREGATE_H

#include "mi_core_database_object_aggregate.h"

namespace Mi {
namespace Core {
namespace Database {
namespace ObjectList {

class MI_CORE_EXPORT Aggregate : public Object::Aggregate
{
    friend class ModelItemList;

    const int _listType;
    QList<IAggregate*> _objects;

protected:
    Aggregate(int listType = UnknownItem)
        :   _listType(listType)
    {}

    IAggregate *initialize();
    ~Aggregate();

    int listType() const
    {
        return _listType;
    }

    QList<IAggregate*> &objects()
    {
        return _objects;
    }

    const QList<IAggregate*> &objects() const
    {
        return _objects;
    }

    bool contains(const QString &name) const;

    int count() const
    {
        return _objects.count();
    }

    IAggregate *at(int i) const
    {
        return _objects.at(i);
    }

    void insert(int i, IAggregate *object);

    bool isList() const
    {
        return true;
    }

    void clear()
    {
        foreach (IAggregate *object, objects()) {
            dynamic_cast<Object::Aggregate*>(object)->setParent(0);
            delete object;
        }
        _objects.clear();
    }
};

}
}
}
}

#endif
