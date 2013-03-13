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

#include "ac_gui_object_graphicsitemupdater.h"
#include "ac_gui_namespace.h"
#include <igraphicsentitydata.h>
#include <igraphicsitem.h>
#include <igraphicsiteminfo.h>
#include <igraphicssubentitydata.h>
#include <imodelitem.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

using namespace Ac;

namespace Object {

void GraphicsItemUpdater::endChangeParent(const IModelItem *child)
{
    if (!child)
        return;
    IGraphicsSubEntityData *child_gdata = QUERY(IGraphicsSubEntityData, child);
    if (!child_gdata)
        return;
    IGraphicsItem *child_gitem = QUERY(IGraphicsItem, child);
    if (!child_gitem)
        return;
    QGraphicsItem *child_node = child_gdata->node();
    if (!child_node)
        return;
    QGraphicsItem *parent_node = 0;
    IGraphicsSubEntityData *parent_gdata = QUERY(IGraphicsSubEntityData, child_gitem->parent());
    if (parent_gdata) {
        parent_node = parent_gdata->node();
    } else {
        IGraphicsEntityData *parent_gdata = QUERY(IGraphicsEntityData, child_gitem->parent());
        IGraphicsItemInfo *child_info = QUERY(IGraphicsItemInfo, child);
        parent_node = parent_gdata->node(child_info->sceneType(), child_info->transformType());
    }
    child_node->setParentItem(parent_node);
    if (!parent_node) {
        QGraphicsScene *scene = child_node->scene();
        if (scene)
            scene->removeItem(child_node);
    }
}

}
