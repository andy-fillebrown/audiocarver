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

#include "ac_gui_base_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <imodelitem.h>

using namespace Ac;
using namespace Mi;

namespace Base {

void *GraphicsItem::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    _aggregate->appendComponent(this);
}

IGraphicsItem *GraphicsItem::parent() const
{
    IModelItem *parent_item = query<IModelItem>(this)->parent();
    if (parent_item && parent_item->isTypeOfItem(ListItem))
        parent_item = parent_item->parent();
    return query<IGraphicsItem>(parent_item);
}

int GraphicsItem::itemCount() const
{
    return query<IModelItem>(this)->itemCount();
}

IGraphicsItem *GraphicsItem::itemAt(int i) const
{
    return query<IGraphicsItem>(query<IModelItem>(this)->itemAt(i));
}

IGraphicsItem *GraphicsItem::findItem(int itemType) const
{
    return query<IGraphicsItem>(query<IModelItem>(this)->findItem(itemType));
}

}
