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

#include "ac_gui_gridline_entity.h"
#include "ac_gui_graphicsitem.h"
#include <imodeldata.h>

using namespace Ac;

namespace GridLine {

Entity::~Entity()
{
    delete _labelSceneLineItem;
    delete _labelSceneTextItem;
    delete _labelSceneRootItem;
}

IUnknown *Entity::initialize()
{
    _labelSceneRootItem = new GraphicsItem;
    _labelSceneTextItem = new GraphicsTextItem(_labelSceneRootItem);
    _labelSceneLineItem = new QGraphicsLineItem(_labelSceneRootItem);
    return Object::Entity::initialize();
}

void Entity::update(int role)
{
    switch (role) {
    case LabelRole:
        labelSceneTextItem()->setText(query<IModelData>(this)->get<QString>(LabelRole));
    }
}

bool Entity::isVisible() const
{
    return labelSceneRootItem()->isVisible();
}

}
