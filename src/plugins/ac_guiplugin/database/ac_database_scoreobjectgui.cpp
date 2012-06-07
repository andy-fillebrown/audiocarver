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

static void setParentGraphicsItems(const QMap<int, QGraphicsItem*> &parentItems,
                                   const QMap<int, QGraphicsItem*> &items)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *parentItem = parentItems.value(i, 0);
        QGraphicsItem *item = items.value(i, 0);
        if (item && parentItem)
            item->setParentItem(parentItem);
    }
}

static void clearParentGraphicsItems(const QMap<int, QGraphicsItem*> &items)
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

static void clearGraphicsItems(IParentEntity *child)
{
    ScoreObjectGui::ParentEntity *child_implementation = dynamic_cast<ScoreObjectGui::ParentEntity*>(child);
    if (!child_implementation)
        return;
    clearParentGraphicsItems(child_implementation->mainGraphicsItems());
    clearParentGraphicsItems(child_implementation->unitXGraphicsItems());
    clearParentGraphicsItems(child_implementation->unitYGraphicsItems());
}

static void setGraphicsItems(IParentEntity *parent, IParentEntity *child)
{
    if (!parent)
        return;
    ScoreObjectGui::ParentEntity *parent_implementation = dynamic_cast<ScoreObjectGui::ParentEntity*>(parent);
    if (!parent_implementation)
        return;
    ScoreObjectGui::ParentEntity *child_implementation = dynamic_cast<ScoreObjectGui::ParentEntity*>(child);
    if (!child_implementation)
        return;
    setParentGraphicsItems(parent_implementation->mainGraphicsItems(), child_implementation->mainGraphicsItems());
}

void ScoreObjectGui::parentChanged(ScoreObject *scoreObject)
{
    Object *parent = scoreObject->parent();
    if (parent)
        setGraphicsItems(query<IParentEntity>(parent), query<IParentEntity>(scoreObject));
    else
        clearGraphicsItems(query<IParentEntity>(scoreObject));
}

IAggregate *ScoreObjectGui::ParentEntity::init()
{
    return this;
}

IAggregate *ScoreObjectGui::ChildEntity::init()
{
    return this;
}

} // namespace Database