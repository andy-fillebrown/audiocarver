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

#include "ac_gui_scoreobject.h"

#include <QGraphicsItem>
#include <QGraphicsScene>

namespace Ac {
namespace Gui {

IAggregator *ScoreObject::init()
{
    return this;
}

IAggregate *ScoreObject::ParentEntity::init()
{
    return this;
}

void ScoreObject::ParentEntity::update(int role)
{
    switch (role) {
    case Mi::ParentRole: {
        IParentEntity *parent = query<IChildEntity>(a())->parentEntity();
        if (!parent)
            return;
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            for (int j = 0;  j < Ac::GraphicsItemTransformTypeCount;  ++j) {
                QGraphicsItem *parent_item = parent->graphicsItem(i, j);
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

IAggregate *ScoreObject::ChildEntity::init()
{
    return this;
}

} // namespace Gui
} // namespace Ac
