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

#include "ac_gui_object_modelitemwatcher.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

using namespace Ac;

namespace Object {

void *ModelItemWatcher::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelItemWatcher*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *ModelItemWatcher::initialize()
{
    return aggregate()->append(this);
}

void ModelItemWatcher::beginChangeParent(const IModelItem *child)
{}

void ModelItemWatcher::endChangeParent(const IModelItem *child)
{
    if (!child)
        return;
    IGraphicsItem *parent_graphics_item = 0;
    IModelItem *parent_model_item = child->parent();
    if (parent_model_item && parent_model_item->isList())
        parent_model_item = parent_model_item->parent();
    parent_graphics_item = query<IGraphicsItem>(parent_model_item);
    IGraphicsItem *child_graphics_item = query<IGraphicsItem>(child);
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        for (int j = 0;  j < TransformTypeCount;  ++j) {
            QGraphicsItem *child_node = child_graphics_item ? child_graphics_item->node(i, j) : 0;
            if (!child_node)
                continue;
            QGraphicsItem *parent_node = parent_graphics_item ? parent_graphics_item->node(i, j) : 0;
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
