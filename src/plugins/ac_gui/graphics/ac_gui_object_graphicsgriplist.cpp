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

#include "ac_gui_object_graphicsgriplist.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <idatabase.h>
#include <igraphicsitem.h>
#include <igraphicsgrip.h>
#include <imodelitem.h>

using namespace Ac;

namespace Object {

GraphicsGripList::GraphicsGripList(IAggregate *aggregate)
    :   Base::GraphicsGripList(aggregate)
    ,   _node(new GraphicsNode)
{
    _node->setVisible(false);
    _node->setZValue(Q_FLOAT_MAX);
}

void GraphicsGripList::initialize()
{
    IGraphicsItem *this_item = query<IGraphicsItem>(this);
    IGraphicsItem *root_item = query<IGraphicsItem>(IDatabase::instance()->rootItem());
    QGraphicsItem *root_node = root_item->findNode(this_item->sceneType(), MainTransform);
    _node->setParentItem(root_node);
}

QGraphicsItem *GraphicsGripList::findNode() const
{
    return _node;
}

void GraphicsGripList::update(int role, const QVariant &value)
{
    if (HighlightRole == role)
        _node->setVisible(FullHighlight == qvariant_cast<int>(value));
}

}
