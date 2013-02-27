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

#include "ac_gui_horizontalgridline_graphicsdata.h"
#include "ac_gui_graphicsnode.h"
#include <ac_core_constants.h>
#include <QPen>

using namespace Ac;
using namespace Mi;

namespace HorizontalGridLine {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   GridLine::GraphicsData(aggregate)
    ,   _editorSceneLineNode(0)
    ,   _editorSceneLineExtensionNode(0)
{
    _editorSceneLineNode = new QGraphicsLineItem;
    _editorSceneLineExtensionNode = new QGraphicsLineItem(_editorSceneLineNode);
    QPen pen(DEFAULT_GRIDLINE_COLOR);
    pen.setCosmetic(true);
    pen.setStyle(GridLine::GraphicsData::gridLinePenStyle());
    _editorSceneLineNode->setPen(pen);
    pen.setStyle(GridLine::GraphicsData::gridLineExtensionPenStyle());
    _editorSceneLineExtensionNode->setPen(pen);
}

GraphicsData::~GraphicsData()
{
    delete _editorSceneLineExtensionNode;
    delete _editorSceneLineNode;
}

void GraphicsData::update(int role, const QVariant &value)
{
    switch (role) {
    case VisibilityRole: {
        const bool visible = qvariant_cast<bool>(value);
        _editorSceneLineNode->setVisible(visible);
        _editorSceneLineExtensionNode->setVisible(visible);
    }   break;
    case LocationRole: {
        qreal location = qvariant_cast<qreal>(value);
        labelSceneRootNode()->setPos(0.0f, location);
        _editorSceneLineNode->setLine(0.0f, location, 1.0f, location);
        _editorSceneLineExtensionNode->setLine(1.0f, location, 2.0f, location);
    } break;
    case ColorRole: {
        const QColor color = qvariant_cast<QColor>(value);
        QPen pen = _editorSceneLineNode->pen();
        pen.setColor(color);
        _editorSceneLineNode->setPen(pen);
        pen = _editorSceneLineExtensionNode->pen();
        pen.setColor(color);
        _editorSceneLineExtensionNode->setPen(pen);
    } break;
    }
    GridLine::GraphicsData::update(role, value);
}

}
