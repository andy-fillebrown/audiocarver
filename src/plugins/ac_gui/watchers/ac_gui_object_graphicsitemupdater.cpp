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

#include "ac_gui_object_graphicsitemupdater.h"
#include <iaggregate.h>
#include <igraphicsdata.h>
#include <igraphicsitem.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

namespace Object {

GraphicsItemUpdater::GraphicsItemUpdater(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    _aggregate->append(this);
}

void *GraphicsItemUpdater::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

void GraphicsItemUpdater::endChangeParent(const IModelItem *child)
{
    if (!child)
        return;
    IGraphicsData *child_gdata = query<IGraphicsData>(child);
    if (!child_gdata)
        return;
    IGraphicsItem *child_gitem = query<IGraphicsItem>(child);
    if (!child_gitem)
        return;
    IGraphicsData *parent_gdata = query<IGraphicsData>(child_gitem->parent());
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        for (int j = 0;  j < TransformTypeCount;  ++j) {
            QGraphicsItem *child_node = child_gdata ? child_gdata->node(i, j) : 0;
            if (!child_node)
                continue;
            QGraphicsItem *parent_node = parent_gdata ? parent_gdata->node(i, j) : 0;
            child_node->setParentItem(parent_node);
            if (!parent_node) {
                QGraphicsScene *scene = child_node->scene();
                if (scene)
                    scene->removeItem(child_node);
            }
        }
    }
}

}
