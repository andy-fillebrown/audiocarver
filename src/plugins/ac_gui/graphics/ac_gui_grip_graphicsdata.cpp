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

#include "ac_gui_grip_graphicsdata.h"
//#include <ac_gripselectionmodel.h>
#include "ac_gui_constants.h"
#include "ac_gui_graphicsgripnode.h"
#include <igraphicsitem.h>
#include <imodelitem.h>

using namespace Ac;
using namespace Qt;

namespace Grip {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Base::GraphicsSubEntityData(aggregate)
    ,   _gripNode(0)
{
    _gripNode = new GraphicsGripNode;
}

GraphicsData::~GraphicsData()
{
    delete _gripNode;
}

void GraphicsData::initialize()
{
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    _gripNode->setData(0, quintptr(this_gitem));
    IGraphicsSubEntityData *parent_gdata = QUERY(IGraphicsSubEntityData, this_gitem->parent());
    _gripNode->setParentItem(parent_gdata->node());
}

QGraphicsItem *GraphicsData::node() const
{
    return _gripNode;
}

void GraphicsData::update(int role, const QVariant &value)
{
    switch (role) {
    case HighlightRole:
        _gripNode->highlight(qvariant_cast<int>(value));
        break;
    case PositionRole:
        _gripNode->setPos(qvariant_cast<QPointF>(value));
        break;
    }
}

}
