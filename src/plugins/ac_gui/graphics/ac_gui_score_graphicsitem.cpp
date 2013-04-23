/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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
#include <imodelitem.h>
#include <QGraphicsItem>

using namespace Ac;

namespace Score {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   ScoreObject::GraphicsItem(aggregate)
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QMap<int, QGraphicsItem*> &main_nodes = mainNodes();
        QGraphicsItem *current_node = main_nodes.value(i);
        delete current_node;
        QGraphicsItem *new_node = new GraphicsRootNode;
        main_nodes.insert(i, new_node);
        _unitXNodes.insert(i, new GraphicsNode(new_node));
        _unitYNodes.insert(i, new GraphicsNode(new_node));
    }
    _unitYNodes[PitchScene]->setTransform(QTransform::fromScale(1.0f, 127.0f));
    update(LengthRole, query<IModelItem>(this)->getValue(LengthRole));
}

GraphicsItem::~GraphicsItem()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        qDelete(_unitYNodes, i);
        qDelete(_unitXNodes, i);
    }
    // Main nodes get deleted in ScoreObject::GraphicsItem destructor.
}

QGraphicsItem *GraphicsItem::findNode(int sceneType, int transformType) const
{
    switch (transformType) {
    case UnitXTransform:
        return _unitXNodes.value(sceneType);
    case UnitYTransform:
        return _unitYNodes.value(sceneType);
    default:
        return ScoreObject::GraphicsItem::findNode(sceneType, transformType);
    }
}

void GraphicsItem::update(int role, const QVariant &value)
{
    if (LengthRole == role) {
        const qreal score_length = qvariant_cast<qreal>(value);
        _unitXNodes[PitchScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
        _unitXNodes[ControlScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
        return;
    }
    ScoreObject::GraphicsItem::update(role, value);
}

}
