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

#include "ac_gui_scoreobject_entity.h"
#include "ac_gui_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>
#include <igraphicsitem.h>
#include <imodelitemlist.h>
#include <isubentity.h>
#include <QGraphicsScene>

using namespace Ac;
using namespace Mi;

static void highlightHelper(IParentEntity *entity, int sceneType, bool highlight)
{
    foreach (ISubEntity *sub_entity, entity->subEntities(sceneType)) {
        IGraphicsItem *graphics_item = query<IGraphicsItem>(sub_entity);
        if (graphics_item) {
            if (highlight)
                graphics_item->highlight();
            else
                graphics_item->unhighlight();
        }
    }
}

namespace ScoreObject {

IUnknown *Entity::initialize()
{
    _mainGraphicsItems.insert(PitchScene, new GraphicsItem);
    _mainGraphicsItems.insert(ControlScene, new GraphicsItem);
    return Object::ParentEntity::initialize();
}

QList<ISubEntity*> Entity::subEntities(int sceneType) const
{
    QList<ISubEntity*> sub_entities;
    switch (sceneType) {
    case PitchScene: {
        IModelItem *pitch_curve = query<IModelItem>(this)->findItem(PitchCurveItem);
        sub_entities.append(query<ISubEntity>(pitch_curve));
        break;
    }
    case ControlScene: {
        IModelItemList *control_curves = query<IModelItem>(this)->findList(ControlCurveItem);
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

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    switch (transformType) {
    case MainTransform:
        return _mainGraphicsItems.value(sceneType);
    default:
        return 0;
    }
}

void Entity::highlight()
{
    highlightHelper(this, PitchScene, true);
    highlightHelper(this, ControlScene, true);
}

void Entity::unhighlight()
{
    highlightHelper(this, PitchScene, false);
    highlightHelper(this, ControlScene, false);
}

}
