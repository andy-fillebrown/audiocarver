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
#include <ac_core_constants.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>

using namespace Ac;
using namespace Mi;

namespace TimeGridLine {

Entity::~Entity()
{
    delete _controlSceneLineItem;
    delete _pitchSceneLineItem;
    delete _labelSceneLineItem;
}

IUnknown *Entity::initialize()
{
    GridLine::Entity::initialize();
    _labelSceneLineItem = new QGraphicsLineItem(labelSceneRootItem());
    _labelSceneLineItem->setLine(0.0f, -10.0f, 0.0f, 10.0f);
    _pitchSceneLineItem = new QGraphicsLineItem;
    _pitchSceneLineHighExtensionItem = new QGraphicsLineItem(_pitchSceneLineItem);
    _pitchSceneLineLowExtensionItem = new QGraphicsLineItem(_pitchSceneLineItem);
    _controlSceneLineItem = new QGraphicsLineItem;
    _controlSceneLineExtensionItem = new QGraphicsLineItem(_controlSceneLineItem);
    QPen pen(DEFAULT_GRIDLINE_COLOR);
    pen.setCosmetic(true);
    pen.setStyle(GridLine::Entity::gridLinePenStyle());
    _pitchSceneLineItem->setPen(pen);
    _controlSceneLineItem->setPen(pen);
    pen.setStyle(GridLine::Entity::gridLineExtensionPenStyle());
    _labelSceneLineItem->setPen(pen);
    _pitchSceneLineHighExtensionItem->setPen(pen);
    _pitchSceneLineLowExtensionItem->setPen(pen);
    _controlSceneLineExtensionItem->setPen(pen);
    return this;
}

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    if (UnitYTransform == transformType) {
        switch (sceneType) {
        case ControlScene:
            return _controlSceneLineItem;
        case PitchScene:
            return _pitchSceneLineItem;
        }
    } else if (MainTransform == transformType && TimeLabelScene == sceneType)
        return labelSceneRootItem();
    return 0;
}

void Entity::update(int role)
{
    switch (role) {
    case VisibilityRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const bool visible = data->get<bool>(VisibilityRole);
        _pitchSceneLineItem->setVisible(visible);
        _controlSceneLineItem->setVisible(visible);
    }   break;
    case LocationRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const qreal location = data->get<qreal>(LocationRole);
        labelSceneRootItem()->setPos(location, 0.0f);
        _pitchSceneLineItem->setLine(location, 0.0f, location, 1.0f);
        _pitchSceneLineHighExtensionItem->setLine(location, 1.0f, location, 2.0f);
        _pitchSceneLineLowExtensionItem->setLine(location, -1.0f, location, 0.0f);
        _controlSceneLineItem->setLine(location, 0.0f, location, 1.0f);
        _controlSceneLineExtensionItem->setLine(location, 1.0f, location, 2.0f);
    }   break;
    case ColorRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        const int color = intFromColor(data->get<QString>(ColorRole));
        QPen pen = _labelSceneLineItem->pen();
        pen.setColor(color);
        _labelSceneLineItem->setPen(pen);
        pen = _pitchSceneLineItem->pen();
        pen.setColor(color);
        _pitchSceneLineItem->setPen(pen);
        pen = _pitchSceneLineHighExtensionItem->pen();
        pen.setColor(color);
        _pitchSceneLineHighExtensionItem->setPen(pen);
        pen = _pitchSceneLineLowExtensionItem->pen();
        pen.setColor(color);
        _pitchSceneLineLowExtensionItem->setPen(pen);
        pen = _controlSceneLineItem->pen();
        pen.setColor(color);
        _controlSceneLineItem->setPen(pen);
        pen = _controlSceneLineExtensionItem->pen();
        pen.setColor(color);
        _controlSceneLineExtensionItem->setPen(pen);
    }   break;
    }
    GridLine::Entity::update(role);
}

}
