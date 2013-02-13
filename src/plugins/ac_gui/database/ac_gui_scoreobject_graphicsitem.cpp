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

#include "ac_gui_scoreobject_graphicsitem.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <igraphicsitem.h>
#include <imodeldata.h>
#include <imodelitemlist.h>
#include <QGraphicsScene>

using namespace Ac;
using namespace Mi;

namespace ScoreObject {

IUnknown *GraphicsItem::initialize()
{
    _mainNodes.insert(PitchScene, new GraphicsNode);
    _mainNodes.insert(ControlScene, new GraphicsNode);
    return Object::GraphicsItem::initialize();
}

QGraphicsItem *GraphicsItem::node(int sceneType, int transformType) const
{
    switch (transformType) {
    case MainTransform:
        return _mainNodes.value(sceneType);
    default:
        return 0;
    }
}

void GraphicsItem::update(int role)
{
    if (VisibilityRole == role) {
        bool visible = query<IModelData>(this)->get<bool>(VisibilityRole);
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            QGraphicsItem *node = this->node(i, MainTransform);
            if (node)
                node->setVisible(visible);
        }
    }
}

}
