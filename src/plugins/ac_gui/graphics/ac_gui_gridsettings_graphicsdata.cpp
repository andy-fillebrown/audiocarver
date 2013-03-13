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

#include "ac_gui_gridsettings_graphicsdata.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"

using namespace Ac;

namespace GridSettings {

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Base::GraphicsEntityData(aggregate)
{
    _mainNodes.insert(TimeLabelScene, new GraphicsNode);
    _mainNodes.insert(PitchLabelScene, new GraphicsNode);
    _mainNodes.insert(ControlLabelScene, new GraphicsNode);
    _unitXNodes.insert(PitchScene, new GraphicsNode);
    _unitXNodes.insert(ControlScene, new GraphicsNode);
    _unitYNodes.insert(PitchScene, new GraphicsNode);
    _unitYNodes.insert(ControlScene, new GraphicsNode);
}

QGraphicsItem *GraphicsData::node(int sceneType, int transformType) const
{
    switch (transformType) {
    case MainTransform:
        return _mainNodes.value(sceneType);
    case UnitXTransform:
        return _unitXNodes.value(sceneType);
    case UnitYTransform:
        return _unitYNodes.value(sceneType);
    default:
        return 0;
    }
}

}
