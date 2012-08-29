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

#include "ac_gui_gridsettings_entity.h"
#include "ac_gui_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <isubentity.h>

using namespace Ac;

namespace GridSettings {

IUnknown *Entity::initialize()
{
    _mainGraphicsItems.insert(TimeLabelScene, new GraphicsItem);
    _mainGraphicsItems.insert(PitchLabelScene, new GraphicsItem);
    _mainGraphicsItems.insert(ControlLabelScene, new GraphicsItem);
    _unitXGraphicsItems.insert(PitchScene, new GraphicsItem);
    _unitXGraphicsItems.insert(ControlScene, new GraphicsItem);
    _unitYGraphicsItems.insert(PitchScene, new GraphicsItem);
    _unitYGraphicsItems.insert(ControlScene, new GraphicsItem);
    return Object::ParentEntity::initialize();
}

QList<ISubEntity*> Entity::subEntities(int sceneType) const
{
    return QList<ISubEntity*>();
}

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    switch (transformType) {
    case MainTransform:
        return _mainGraphicsItems.value(sceneType);
    case UnitXTransform:
        return _unitXGraphicsItems.value(sceneType);
    case UnitYTransform:
        return _unitYGraphicsItems.value(sceneType);
    default:
        return 0;
    }
}

}
