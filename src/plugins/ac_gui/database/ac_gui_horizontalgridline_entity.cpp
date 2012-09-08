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

#include "ac_gui_horizontalgridline_entity.h"
#include "ac_gui_graphicsitem.h"
#include <ac_core_constants.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>
#include <QPen>

using namespace Ac;
using namespace Mi;

namespace HorizontalGridLine {

Entity::~Entity()
{
    delete _editorSceneLineExtensionItem;
    delete _editorSceneLineItem;
}

IUnknown *Entity::initialize()
{
    _editorSceneLineItem = new QGraphicsLineItem;
    _editorSceneLineExtensionItem = new QGraphicsLineItem(_editorSceneLineItem);
    QPen pen(DEFAULT_GRIDLINE_COLOR);
    pen.setCosmetic(true);
    pen.setStyle(GridLine::Entity::gridLinePenStyle());
    _editorSceneLineItem->setPen(pen);
    pen.setStyle(GridLine::Entity::gridLineExtensionPenStyle());
    _editorSceneLineExtensionItem->setPen(pen);
    return GridLine::Entity::initialize();
}

void Entity::update(int role)
{
    switch (role) {
    case VisibilityRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const bool visible = data->get<bool>(VisibilityRole);
        _editorSceneLineItem->setVisible(visible);
        _editorSceneLineExtensionItem->setVisible(visible);
    }   break;
    case LocationRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        qreal location = data->get<qreal>(LocationRole);
        labelSceneRootItem()->setPos(0.0f, location);
        _editorSceneLineItem->setLine(0.0f, location, 1.0f, location);
        _editorSceneLineExtensionItem->setLine(1.0f, location, 2.0f, location);
    } break;
    case ColorRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const int color = intFromColor(data->get<QString>(ColorRole));
        QPen pen = _editorSceneLineItem->pen();
        pen.setColor(color);
        _editorSceneLineItem->setPen(pen);
        pen = _editorSceneLineExtensionItem->pen();
        pen.setColor(color);
        _editorSceneLineExtensionItem->setPen(pen);
    } break;
    }
    GridLine::Entity::update(role);
}

}
