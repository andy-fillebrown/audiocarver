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

#include "ac_gui_score_entity.h"
#include "ac_gui_graphicsrootitem.h"
#include "ac_gui_namespace.h"
#include <ac_core_constants.h>
#include <imodeldata.h>
#include <imodelitem.h>

using namespace Ac;

namespace Score {

IUnknown *Entity::initialize()
{
    QMap<int, QGraphicsItem*> &main_graphics_items = mainGraphicsItems();
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *main_graphics_item = new GraphicsRootItem;
        main_graphics_items.insert(i, main_graphics_item);
        _unitXGraphicsItems.insert(i, new GraphicsItem(main_graphics_item));
        _unitYGraphicsItems.insert(i, new GraphicsItem(main_graphics_item));
    }
    _unitXGraphicsItems[PitchScene]->setTransform(QTransform::fromScale(DEFAULT_SCORE_LENGTH, 1.0f));
    _unitXGraphicsItems[ControlScene]->setTransform(QTransform::fromScale(DEFAULT_SCORE_LENGTH, 1.0f));
    _unitYGraphicsItems[PitchScene]->setTransform(QTransform::fromScale(1.0f, 127.0f));
    return Object::ParentEntity::initialize();
}

QGraphicsItem *Entity::graphicsItem(int sceneType, int transformType) const
{
    switch (transformType) {
    case UnitXTransform:
        return _unitXGraphicsItems.value(sceneType);
    case UnitYTransform:
        return _unitYGraphicsItems.value(sceneType);
    default:
        return ScoreObject::Entity::graphicsItem(sceneType, transformType);
    }
}

void Entity::update(int role)
{
    switch (role) {
    case LengthRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        qreal score_length = data->get<qreal>(LengthRole);
        _unitXGraphicsItems[PitchScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
        _unitXGraphicsItems[ControlScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
    }   break;
    }
    ScoreObject::Entity::update(role);
}

}
