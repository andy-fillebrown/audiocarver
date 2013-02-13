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

#include "ac_gui_object_graphicsentity.h"
#include "ac_gui_namespace.h"
#include "ac_gui_graphicsnode.h"
#include <iaggregate.h>

using namespace Ac;

namespace Object {

void *GraphicsEntity::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<GraphicsEntity*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *GraphicsEntity::initialize()
{
    _mainNodes.insert(PitchScene, new GraphicsNode);
    _mainNodes.insert(ControlScene, new GraphicsNode);
    return aggregate()->append(this);
}

QGraphicsItem *GraphicsEntity::node(int sceneType, int transformType) const
{
    switch (transformType) {
    case MainTransform:
        return _mainNodes.value(sceneType);
    default:
        return 0;
    }
}

}
