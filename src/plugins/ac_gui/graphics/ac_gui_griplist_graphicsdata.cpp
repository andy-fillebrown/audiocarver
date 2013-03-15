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

#include "ac_gui_griplist_graphicsdata.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <igraphicsitem.h>
#include <imodelitem.h>

using namespace Ac;

namespace GripList {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Base::GraphicsSubEntityData(aggregate)
    ,   _node(new GraphicsNode)
{}

GraphicsData::~GraphicsData()
{
    delete _node;
}

void GraphicsData::initialize()
{
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    IGraphicsItem *parent_gitem = this_gitem->parent();
    if (!parent_gitem)
        return;
    IGraphicsSubEntityData *parent_gdata = QUERY(IGraphicsSubEntityData, parent_gitem);
    _node->setParentItem(parent_gdata->node());
}

QGraphicsItem *GraphicsData::node() const
{
    return _node;
}

void GraphicsData::update(int role, const QVariant &value)
{
}

}
