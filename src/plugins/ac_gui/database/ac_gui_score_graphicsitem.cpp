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

#include "ac_gui_score_graphicsitem.h"
#include "ac_gui_graphicsrootnode.h"
#include "ac_gui_namespace.h"
#include <ac_core_constants.h>
#include <imodeldata.h>
#include <imodelitem.h>

using namespace Ac;

namespace Score {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   ScoreObject::GraphicsItem(aggregate)
{
    QMap<int, QGraphicsItem*> &main_nodes = mainNodes();
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *main_node = new GraphicsRootNode;
        main_nodes.insert(i, main_node);
        _unitXNodes.insert(i, new GraphicsNode(main_node));
        _unitYNodes.insert(i, new GraphicsNode(main_node));
    }
    _unitXNodes[PitchScene]->setTransform(QTransform::fromScale(DEFAULT_SCORE_LENGTH, 1.0f));
    _unitXNodes[ControlScene]->setTransform(QTransform::fromScale(DEFAULT_SCORE_LENGTH, 1.0f));
    _unitYNodes[PitchScene]->setTransform(QTransform::fromScale(1.0f, 127.0f));
}

QGraphicsItem *GraphicsItem::node(int sceneType, int transformType) const
{
    switch (transformType) {
    case UnitXTransform:
        return _unitXNodes.value(sceneType);
    case UnitYTransform:
        return _unitYNodes.value(sceneType);
    default:
        return ScoreObject::GraphicsItem::node(sceneType, transformType);
    }
}

void GraphicsItem::update(int role)
{
    switch (role) {
    case LengthRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        qreal score_length = data->get<qreal>(LengthRole);
        _unitXNodes[PitchScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
        _unitXNodes[ControlScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
    }   break;
    }
    ScoreObject::GraphicsItem::update(role);
}

}
