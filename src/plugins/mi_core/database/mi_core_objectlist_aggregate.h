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

#ifndef MI_CORE_OBJECTLIST_AGGREGATE_H
#define MI_CORE_OBJECTLIST_AGGREGATE_H

#include "mi_core_object_aggregate.h"

namespace ObjectList {

class MI_CORE_EXPORT Aggregate : public Object::Aggregate
{
    int _listType;
    QList<IAggregate*> _items;

public:
    Aggregate(IAggregate *parent)
        :   Object::Aggregate(parent)
        ,   _listType(0)
    {
        Q_ASSERT(parent);
    }

    int &listType()
    {
        return _listType;
    }

    QList<IAggregate*> &items()
    {
        return _items;
    }
};

}

#endif
