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

#include "ac_gui_object_entity.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>
#include <iaggregate.h>
#include <ichildentity.h>
#include <iparententity.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

using namespace Ac;
using namespace Mi;

namespace Object {

void *Entity::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<Entity*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *Entity::initialize()
{
    aggregate()->append(this);
    return this;
}

void Entity::update(int role)
{
    if (ParentRole == role) {
        IParentEntity *parent = query<IChildEntity>(this)->parent();
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            for (int j = 0;  j < TransformTypeCount;  ++j) {
                QGraphicsItem *parent_item = parent ? parent->graphicsItem(i, j) : 0;
                QGraphicsItem *child_item = graphicsItem(i, j);
                if (!child_item)
                    continue;
                child_item->setParentItem(parent_item);
                if (!parent_item) {
                    QGraphicsScene *scene = child_item->scene();
                    if (scene)
                        scene->removeItem(child_item);
                }
            }
        }
    }
}

}
