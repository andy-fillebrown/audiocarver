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
#include <ichildentity.h>
#include <imodelitem.h>
#include <iparententity.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

using namespace Ac;

namespace Object {

IUnknown *ModelItemWatcher::initialize()
{
    return aggregate()->append(this);
}

void *ModelItemWatcher::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelItemWatcher*>(this);
    return aggregate()->queryInterface(interfaceType);
}

void ModelItemWatcher::beginChangeParent(const IModelItem *child)
{}

void ModelItemWatcher::endChangeParent(const IModelItem *child)
{
    if (!child)
        return;
    IEntity *child_entity = query<IEntity>(child);
    IEntity *parent_entity = query<IChildEntity>(child)->parent();
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        for (int j = 0;  j < TransformTypeCount;  ++j) {
            QGraphicsItem *child_graphics_item = child_entity->graphicsItem(i, j);
            if (!child_graphics_item)
                continue;
            QGraphicsItem *parent_graphics_item = parent_entity ? parent_entity->graphicsItem(i, j) : 0;
            child_graphics_item->setParentItem(parent_graphics_item);
            if (!parent_graphics_item) {
                QGraphicsScene *scene = child_graphics_item->scene();
                if (scene)
                    scene->removeItem(child_graphics_item);
            }
        }
    }
}

}
