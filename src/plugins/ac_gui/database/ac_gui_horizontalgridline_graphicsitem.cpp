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

#include "ac_gui_horizontalgridline_graphicsitem.h"
#include "ac_gui_graphicsnode.h"
#include <ac_core_constants.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>
#include <QPen>

using namespace Ac;
using namespace Mi;

namespace HorizontalGridLine {

IUnknown *GraphicsItem::initialize()
{
    _editorSceneLineNode = new QGraphicsLineItem;
    _editorSceneLineExtensionNode = new QGraphicsLineItem(_editorSceneLineNode);
    QPen pen(DEFAULT_GRIDLINE_COLOR);
    pen.setCosmetic(true);
    pen.setStyle(GridLine::GraphicsItem::gridLinePenStyle());
    _editorSceneLineNode->setPen(pen);
    pen.setStyle(GridLine::GraphicsItem::gridLineExtensionPenStyle());
    _editorSceneLineExtensionNode->setPen(pen);
    return GridLine::GraphicsItem::initialize();
}

GraphicsItem::~GraphicsItem()
{
    delete _editorSceneLineExtensionNode;
    delete _editorSceneLineNode;
}

void GraphicsItem::setColor(int color)
{
    QPen pen = _editorSceneLineNode->pen();
    pen.setColor(color);
    _editorSceneLineNode->setPen(pen);
    pen = _editorSceneLineExtensionNode->pen();
    pen.setColor(color);
    _editorSceneLineExtensionNode->setPen(pen);
    return GridLine::GraphicsItem::setColor(color);
}

void GraphicsItem::update(int role)
{
    switch (role) {
    case VisibilityRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const bool visible = data->get<bool>(VisibilityRole);
        _editorSceneLineNode->setVisible(visible);
        _editorSceneLineExtensionNode->setVisible(visible);
    }   break;
    case LocationRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        qreal location = data->get<qreal>(LocationRole);
        labelSceneRootNode()->setPos(0.0f, location);
        _editorSceneLineNode->setLine(0.0f, location, 1.0f, location);
        _editorSceneLineExtensionNode->setLine(1.0f, location, 2.0f, location);
    } break;
    case ColorRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const int color = intFromColor(data->get<QString>(ColorRole));
        QPen pen = _editorSceneLineNode->pen();
        pen.setColor(color);
        _editorSceneLineNode->setPen(pen);
        pen = _editorSceneLineExtensionNode->pen();
        pen.setColor(color);
        _editorSceneLineExtensionNode->setPen(pen);
    } break;
    }
    GridLine::GraphicsItem::update(role);
}

}
