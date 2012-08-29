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

#include "ac_gui_score_entity.h"
#include "ac_gui_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <imodelitem.h>

using namespace Ac;

namespace Score {

IUnknown *Entity::initialize()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        _unitXGraphicsItems.insert(i, new GraphicsItem);
        _unitYGraphicsItems.insert(i, new GraphicsItem);
    }
    return Object::ParentEntity::initialize();
}

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    switch (transformType) {
    case UnitXTransform:
        return _unitXGraphicsItems.value(sceneType);
    case UnitYTransform:
        return _unitYGraphicsItems.value(sceneType);
    default:
        return ScoreObject::Entity::graphicsItem(sceneType, transformType);
    }
}

}
