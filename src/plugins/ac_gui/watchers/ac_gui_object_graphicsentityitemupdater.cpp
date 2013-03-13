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

#include "ac_gui_object_graphicsentityitemupdater.h"
#include "ac_gui_namespace.h"
#include <igraphicsentitydata.h>
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

using namespace Ac;

namespace Object {

void GraphicsEntityItemUpdater::endChangeParent(const IModelItem *child)
{
    if (!child)
        return;
    IGraphicsEntityData *child_gdata = QUERY(IGraphicsEntityData, child);
    if (!child_gdata)
        return;
    IGraphicsItem *child_gitem = QUERY(IGraphicsItem, child);
    if (!child_gitem)
        return;
    IGraphicsEntityData *parent_gdata = QUERY(IGraphicsEntityData, child_gitem->parent());
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        for (int j = 0;  j < TransformTypeCount;  ++j) {
            QGraphicsItem *child_node = child_gdata->node(i, j);
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
