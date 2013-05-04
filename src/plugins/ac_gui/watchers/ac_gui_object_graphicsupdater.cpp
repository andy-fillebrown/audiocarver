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

#include "ac_gui_object_graphicsupdater.h"
#include "ac_gui_namespace.h"
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

using namespace Ac;

static void updateParentItem(QGraphicsItem *childNode, IGraphicsItem *parentGraphics, int sceneType, int transformType)
{
    QGraphicsItem *parent_node = 0;
    if (parentGraphics)
        parent_node = parentGraphics->findNode(sceneType, transformType);
    childNode->setParentItem(parent_node);
    if (!parent_node) {
        QGraphicsScene *scene = childNode->scene();
        if (scene)
            scene->removeItem(childNode);
    }
}

namespace Object {

void GraphicsUpdater::initialize()
{
    endChangeParent(query<IModelItem>(this));
}

void GraphicsUpdater::endChangeParent(IModelItem *child)
{
    if (!child)
        return;
    IGraphicsItem *child_graphics = query<IGraphicsItem>(child);
    if (!child_graphics)
        return;
    IGraphicsItem *parent_graphics = query<IGraphicsItem>(child_graphics->parent());
    int child_scene_type = child_graphics->sceneType();
    if (UnspecifiedScene == child_scene_type) {
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            for (int j = 0;  j < TransformTypeCount;  ++j) {
                QGraphicsItem *child_node = child_graphics->findNode(i, j);
                if (child_node)
                    updateParentItem(child_node, parent_graphics, i, j);
            }
        }
    } else
        updateParentItem(child_graphics->findNode(), parent_graphics, child_graphics->sceneType(), child_graphics->transformType());
}

void GraphicsUpdater::endChangeData(IModelItem *item, int role)
{
    IGraphicsItem *graphics = query<IGraphicsItem>(item);
    if (graphics)
        graphics->update(role, item->getValue(role));
}

}
