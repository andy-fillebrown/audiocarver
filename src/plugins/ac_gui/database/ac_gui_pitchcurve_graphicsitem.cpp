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

#include "ac_gui_pitchcurve_graphicsitem.h"
#include "ac_gui_graphicscurvenode.h"
#include "ac_gui_namespace.h"
#include <imodelitem.h>

using namespace Ac;

namespace PitchCurve {

IUnknown *GraphicsItem::initialize()
{
    return Curve::GraphicsItem::initialize();
}

QGraphicsItem *GraphicsItem::node(int sceneType, int transformType) const
{
    if (PitchScene == sceneType && MainTransform == transformType)
        return curveNode();
    return 0;
}

void GraphicsItem::update(int role)
{
    Curve::GraphicsItem::update(role);
    if (PointsRole == role) {
        IModelItem *this_item = query<IModelItem>(this);
        if (!this_item)
            return;
        IGraphicsItem *note_graphic = query<IGraphicsItem>(this_item->parent());
        if (!note_graphic)
            return;
        note_graphic->update(VolumeRole);
    }
}

}
