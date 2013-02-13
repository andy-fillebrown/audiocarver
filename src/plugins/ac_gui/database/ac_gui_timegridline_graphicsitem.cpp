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

#include "ac_gui_timegridline_graphicsitem.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <ac_core_constants.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>
#include <QPen>

using namespace Ac;
using namespace Mi;

namespace TimeGridLine {

GraphicsItem::~GraphicsItem()
{
    delete _controlSceneLineNode;
    delete _pitchSceneLineNode;
    delete _labelSceneLineNode;
}

IUnknown *GraphicsItem::initialize()
{
    GridLine::GraphicsItem::initialize();
    _labelSceneLineNode = new QGraphicsLineItem(labelSceneRootNode());
    _labelSceneLineNode->setLine(0.0f, -10.0f, 0.0f, 10.0f);
    _pitchSceneLineNode = new QGraphicsLineItem;
    _pitchSceneLineHighExtensionNode = new QGraphicsLineItem(_pitchSceneLineNode);
    _pitchSceneLineLowExtensionNode = new QGraphicsLineItem(_pitchSceneLineNode);
    _controlSceneLineNode = new QGraphicsLineItem;
    _controlSceneLineExtensionNode = new QGraphicsLineItem(_controlSceneLineNode);
    QPen pen(DEFAULT_GRIDLINE_COLOR);
    pen.setCosmetic(true);
    pen.setStyle(GridLine::GraphicsItem::gridLinePenStyle());
    _pitchSceneLineNode->setPen(pen);
    _controlSceneLineNode->setPen(pen);
    pen.setStyle(GridLine::GraphicsItem::gridLineExtensionPenStyle());
    _labelSceneLineNode->setPen(pen);
    _pitchSceneLineHighExtensionNode->setPen(pen);
    _pitchSceneLineLowExtensionNode->setPen(pen);
    _controlSceneLineExtensionNode->setPen(pen);
    return this;
}

QGraphicsItem *GraphicsItem::node(int sceneType, int transformType) const
{
    if (UnitYTransform == transformType) {
        switch (sceneType) {
        case ControlScene:
            return _controlSceneLineNode;
        case PitchScene:
            return _pitchSceneLineNode;
        }
    } else if (MainTransform == transformType && TimeLabelScene == sceneType)
        return labelSceneRootNode();
    return 0;
}

void GraphicsItem::setColor(int color)
{
    QPen pen = _labelSceneLineNode->pen();
    pen.setColor(color);
    _labelSceneLineNode->setPen(pen);
    pen = _pitchSceneLineNode->pen();
    pen.setColor(color);
    _pitchSceneLineNode->setPen(pen);
    pen = _pitchSceneLineHighExtensionNode->pen();
    pen.setColor(color);
    _pitchSceneLineHighExtensionNode->setPen(pen);
    pen = _pitchSceneLineLowExtensionNode->pen();
    pen.setColor(color);
    _pitchSceneLineLowExtensionNode->setPen(pen);
    pen = _controlSceneLineNode->pen();
    pen.setColor(color);
    _controlSceneLineNode->setPen(pen);
    pen = _controlSceneLineExtensionNode->pen();
    pen.setColor(color);
    _controlSceneLineExtensionNode->setPen(pen);
    GridLine::GraphicsItem::setColor(color);
}

void GraphicsItem::update(int role)
{
    switch (role) {
    case VisibilityRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const bool visible = data->get<bool>(VisibilityRole);
        _pitchSceneLineNode->setVisible(visible);
        _controlSceneLineNode->setVisible(visible);
    }   break;
    case LocationRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const qreal location = data->get<qreal>(LocationRole);
        labelSceneRootNode()->setPos(location, 0.0f);
        _pitchSceneLineNode->setLine(location, 0.0f, location, 1.0f);
        _pitchSceneLineHighExtensionNode->setLine(location, 1.0f, location, 2.0f);
        _pitchSceneLineLowExtensionNode->setLine(location, -1.0f, location, 0.0f);
        _controlSceneLineNode->setLine(location, 0.0f, location, 1.0f);
        _controlSceneLineExtensionNode->setLine(location, 1.0f, location, 2.0f);
    }   break;
    case ColorRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        setColor(intFromColor(data->get<QString>(ColorRole)));
    }   break;
    }
    GridLine::GraphicsItem::update(role);
}

}
