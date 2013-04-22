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

#include "ac_gui_velocity_graphicsdelegate.h"
#include "ac_gui_namespace.h"
#include <igraphicsgrip.h>
#include <igraphicsgriplist.h>
#include <igraphicsitem.h>
#include <imodelitem.h>

using namespace Ac;

namespace Velocity {

void GraphicsDelegate::updateModel()
{
    IGraphicsGripList *griplist = query<IGraphicsGripList>(this);
    PointList points = buildPointList(griplist);
    qreal velocity = points.first().pos.y();
    IGraphicsItem *this_item = query<IGraphicsItem>(this);
    IModelItem *note_item = query<IModelItem>(this_item->parent());
    note_item->set(VolumeRole, velocity);
}

void GraphicsDelegate::updateGraphics()
{
    IGraphicsItem *curve_item = query<IGraphicsItem>(this);
    IGraphicsGripList *griplist = query<IGraphicsGripList>(this);
    griplist->sort();
    curve_item->update(PointsRole, QVariant::fromValue(buildPointList(griplist)));
}

}
