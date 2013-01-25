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

#include "ac_gui_curve_entity.h"
#include "ac_gui_graphicsitem.h"
#include <igraphicsitem.h>
#include <imodeldata.h>

using namespace Ac;

namespace Curve {

IUnknown *Entity::initialize()
{
    return Object::Entity::initialize();
}

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    return query<IGraphicsItem>(this)->graphicsItem(sceneType, transformType);
}

void Entity::update(int role)
{
    switch (role) {
    case PointsRole:
        query<IGraphicsItem>(this)->setPoints(query<IModelData>(this)->get<PointList>(PointsRole));
    }
}

void Entity::highlight(bool on)
{
    query<IGraphicsItem>(this)->highlight(on);
}

bool Entity::isVisible() const
{
    return query<IGraphicsItem>(this)->isVisible();
}

}
