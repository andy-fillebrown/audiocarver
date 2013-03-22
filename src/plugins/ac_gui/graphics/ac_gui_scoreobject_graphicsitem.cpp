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

#include "ac_gui_scoreobject_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <imodelitem.h>

using namespace Ac;

namespace ScoreObject {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   Base::GraphicsItem(aggregate)
    ,   _helper(this)
{}

int GraphicsItem::count() const
{
    IModelItem *this_item = QUERY(IModelItem, this);
    return this_item->count();
}

IGraphicsItem *GraphicsItem::at(int i) const
{
    IModelItem *this_item = QUERY(IModelItem, this);
    return QUERY(IGraphicsItem, this_item->at(i));
}

IGraphicsItem *GraphicsItem::findItem(int itemType) const
{
    IModelItem *this_item = QUERY(IModelItem, this);
    return QUERY(IGraphicsItem, this_item->findItem(itemType));
}

}
