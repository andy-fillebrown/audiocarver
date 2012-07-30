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

#ifndef MI_CORE_DATABASE_OBJECT_AGGREGATE_H
#define MI_CORE_DATABASE_OBJECT_AGGREGATE_H

#include "mi_core_aggregate.h"

namespace Mi {
namespace Core {
namespace Database {

namespace ObjectList {

class Aggregate;
class ModelItemList;

}

namespace Object {

class MI_CORE_EXPORT Aggregate : public Mi::Core::Aggregate
{
    friend class ObjectList::Aggregate;
    friend class ObjectList::ModelItemList;
    friend class ModelData;
    friend class ModelItem;

    enum { RoleCount = 1 };
    enum { ItemCount = 0 };

    QString _name;

    Aggregate *_parent;

protected:
    enum {
        RoleCountOffset = 0,
        TotalRoleCount = RoleCount,
        ItemCountOffset = 0,
        TotalItemCount = ItemCount
    };

    Aggregate()
    {}

    IAggregate *initialize();

    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name);

    Aggregate *parent() const
    {
        if (isList() && _parent)
            return _parent->parent();
        return _parent;
    }

    virtual void setParent(Aggregate *parent);

    virtual bool isList() const
    {
        return false;
    }

    ObjectList::Aggregate *list() const;
};

}
}
}
}

#endif
