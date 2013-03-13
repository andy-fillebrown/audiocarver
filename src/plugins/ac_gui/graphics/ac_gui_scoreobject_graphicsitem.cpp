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
#include "ac_gui_namespace.h"
#include "ac_gui_graphicsnode.h"
#include <imodelitem.h>

using namespace Ac;

namespace ScoreObject {

GraphicsItem::GraphicsItem(IAggregate *aggregate)
    :   Base::GraphicsEntityItem(aggregate)
    ,   _helper(this)
{
    _mainNodes.insert(PitchScene, new GraphicsNode);
    _mainNodes.insert(ControlScene, new GraphicsNode);
}

QList<IGraphicsItem*> GraphicsItem::subentities(int sceneType, int transformType) const
{
    QList<IGraphicsItem*> subents;
    IModelItem *item = QUERY(IModelItem, this);
    if (!item)
        return subents;
    IModelItem *pitch_curve = item->findItem(PitchCurveItem);
    subents.append(QUERY(IGraphicsItem, pitch_curve));
    IModelItem *control_curve = item->findItem(ControlCurveItem);
    subents.append(QUERY(IGraphicsItem, control_curve));
    subents.removeAll(0);
    return subents;
}

}
