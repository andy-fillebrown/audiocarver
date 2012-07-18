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

#include <ac_isubentity.h>
#include <mi_imodellist.h>

#include <mi_core_dataobject.h>

#include <QGraphicsItem>
#include <QGraphicsScene>

using namespace Mi;

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

QList<ISubEntity*> ScoreObject::ParentEntity::subEntities(int sceneType) const
{
    QList<ISubEntity*> sub_entities;
    switch (sceneType) {
    case PitchScene: {
        IModelItem *pitch_curve = query<IModelItem>(a())->findItem(PitchCurveItem);
        sub_entities.append(query<ISubEntity>(pitch_curve));
        break;
    }
    case ControlScene: {
        IModelList *control_curves = query<IModelItem>(a())->findList(ControlCurveItem);
        const int n = control_curves->count();
        for (int i = 0;  i < n;  ++i)
            sub_entities.append(query<ISubEntity>(control_curves->at(i)));
        break;
    }
    default:
        break;
    }
    return sub_entities;
}

void ScoreObject::ParentEntity::update(int role)
{
    switch (role) {
    case ParentRole: {
        IParentEntity *parent = query<IChildEntity>(a())->parentEntity();
        if (!parent)
            return;
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            for (int j = 0;  j < GraphicsItemTransformTypeCount;  ++j) {
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

IParentEntity *ScoreObject::ChildEntity::parentEntity() const
{
    return query<IParentEntity>(query<IModelItem>(a())->parent());
}

} // namespace Gui
} // namespace Ac
