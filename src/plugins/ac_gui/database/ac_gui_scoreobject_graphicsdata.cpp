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

#include "ac_gui_scoreobject_graphicsdata.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <imodeldata.h>
#include <imodelitemlist.h>

using namespace Ac;
using namespace Mi;

namespace ScoreObject {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Object::GraphicsData(aggregate)
{
    _mainNodes.insert(PitchScene, new GraphicsNode);
    _mainNodes.insert(ControlScene, new GraphicsNode);
}

QGraphicsItem *GraphicsData::node(int sceneType, int transformType) const
{
    switch (transformType) {
    case MainTransform:
        return _mainNodes.value(sceneType);
    default:
        return 0;
    }
}

void GraphicsData::update(int role, const QVariant &value)
{
    if (VisibilityRole == role) {
        bool visible = qvariant_cast<bool>(value);
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            QGraphicsItem *node = this->node(i, MainTransform);
            if (node)
                node->setVisible(visible);
        }
    }
}

}