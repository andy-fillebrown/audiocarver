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

#include "ac_gui_scoreobject_graphicsitem.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <imodelitem.h>
#include <QGraphicsItem>

using namespace Ac;

namespace ScoreObject {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   Base::GraphicsItem(aggregate)
{
    _mainNodes.insert(PitchScene, new GraphicsNode);
    _mainNodes.insert(ControlScene, new GraphicsNode);
}

GraphicsItem::~GraphicsItem()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        delete _mainNodes.value(i);
        _mainNodes.insert(i, 0);
    }
}

QGraphicsItem *GraphicsItem::findNode(int sceneType, int transformType) const
{
    if (MainTransform == transformType)
        return _mainNodes.value(sceneType);
    return 0;
}

void GraphicsItem::update(int role, const QVariant &value)
{
    if (VisibilityRole == role) {
        bool visible = qvariant_cast<bool>(value);
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            QGraphicsItem *node = _mainNodes.value(i);
            if (node)
                node->setVisible(visible);
        }
    }
}

}
