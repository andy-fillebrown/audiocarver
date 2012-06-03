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

#include "ac_database_scoreobjectgui.h"

#include <QGraphicsItem>
#include <QGraphicsScene>

namespace Database {

namespace ScoreObjectGui {

IAggregate *ParentEntity::init()
{
    return this;
}

void setParentGraphicsItems(const QMap<int, QGraphicsItem*> &parentItems,
                            const QMap<int, QGraphicsItem*> &items)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *parentItem = parentItems.value(i, 0);
        QGraphicsItem *item = items.value(i, 0);
        if (item && parentItem)
            item->setParentItem(parentItem);
    }
}

void clearParentGraphicsItems(const QMap<int, QGraphicsItem*> &items)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *item = items.value(i, 0);
        if (item) {
            item->setParentItem(0);
            QGraphicsScene *scene = item->scene();
            if (scene)
                scene->removeItem(item);
        }
    }
}

} // namespace ScoreObjectGui

} // namespace Database
