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
#include <idatabaseobjectfactory.h>
#include <imodelitem.h>
#include <QGraphicsItem>

using namespace Ac;

namespace Score {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   ScoreObject::GraphicsItem(aggregate)
    ,   _playCursor(0)
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
    _playCursor = IDatabaseObjectFactory::instance()->create(PlayCursorItem, this);
    IGraphicsItem *play_cursor = query<IGraphicsItem>(_playCursor);
    _unitYNodes.insert(TimeLabelScene, play_cursor->findNode(TimeLabelScene, UnitYTransform));
    _unitYNodes.insert(PitchLabelScene, play_cursor->findNode(PitchLabelScene, UnitYTransform));
    _unitYNodes.insert(ControlLabelScene, play_cursor->findNode(ControlLabelScene, UnitYTransform));
}

GraphicsItem::~GraphicsItem()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        qDelete(_unitYNodes, i);
        qDelete(_unitXNodes, i);
    }
    qDelete(_playCursor);
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

IGraphicsItem *GraphicsItem::itemAt(int i) const
{
    if (ScoreObject::GraphicsItem::itemCount() == i)
        return query<IGraphicsItem>(_playCursor);
    return ScoreObject::GraphicsItem::itemAt(i);
}

IGraphicsItem *GraphicsItem::findItem(int itemType) const
{
    if (PlayCursorItem == itemType)
        return query<IGraphicsItem>(_playCursor);
    return ScoreObject::GraphicsItem::findItem(itemType);
}

void GraphicsItem::update(int role, const QVariant &value)
{
    if (LengthRole == role) {
        const qreal score_length = qvariant_cast<qreal>(value);
        _unitXNodes[PitchScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
        _unitXNodes[ControlScene]->setTransform(QTransform::fromScale(score_length, 1.0f));
        return;
    }
    if (role == PlaybackTimeRole || role == StartTimeRole) {
        query<IGraphicsItem>(_playCursor)->update(PlaybackTimeRole, value);
        return;
    }
    ScoreObject::GraphicsItem::update(role, value);
}

}
