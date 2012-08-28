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

#include "ac_gui_timegridline_entity.h"
#include "ac_gui_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <QGraphicsLineItem>

using namespace Ac;

namespace TimeGridLine {

Entity::~Entity()
{
    delete _controlSceneLineItem;
    delete _pitchSceneLineItem;
}

IUnknown *Entity::initialize()
{
    _pitchSceneLineItem = new QGraphicsLineItem;
    _controlSceneLineItem = new QGraphicsLineItem;
    return GridLine::Entity::initialize();
}

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    if (UnitYTransform == transformType) {
        switch (sceneType) {
        case ControlScene:
            return controlSceneLineItem();
        case PitchScene:
            return pitchSceneLineItem();
        }
    } else if (MainTransform == transformType && TimeLabelScene == sceneType)
        return labelRootItem();
    return 0;
}

void Entity::update(int role)
{
    GridLine::Entity::update(role);
}

}
