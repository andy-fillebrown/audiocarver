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

#include "ac_gui_controlgridline_entity.h"
#include "ac_gui_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <QGraphicsLineItem>

using namespace Ac;

namespace ControlGridLine {

IUnknown *Entity::initialize()
{
    return HorizontalGridLine::Entity::initialize();
}

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    if (ControlScene == sceneType && UnitXTransform == transformType)
        return editorSceneLineItem();
    if (ControlLabelScene == sceneType && MainTransform == transformType)
        return labelSceneRootItem();
    return HorizontalGridLine::Entity::graphicsItem(sceneType, transformType);
}

void Entity::update(int role)
{
    HorizontalGridLine::Entity::update(role);
}

}
