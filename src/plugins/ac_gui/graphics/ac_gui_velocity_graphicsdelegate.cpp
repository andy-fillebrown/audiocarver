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
#include <igraphicsitem.h>
#include <igripdata.h>
#include <igriplistdata.h>
#include <imodeldata.h>

using namespace Ac;

namespace Velocity {

void GraphicsDelegate::updateModel()
{
    PointList points = buildPointList();
    qreal velocity = points.first().pos.y();
    IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
    IGraphicsItem *note_gitem = this_gitem->parent();
    IModelData *note_gdata = QUERY(IModelData, note_gitem);
    note_gdata->set(velocity, VolumeRole);
}

void GraphicsDelegate::updateGraphics()
{
    IGraphicsData *curve_gdata = QUERY(IGraphicsData, this);
    IGripListData *griplist_gdata = findGripListData();
    griplist_gdata->sort();
    curve_gdata->update(PointsRole, QVariant::fromValue(buildPointList()));
}

}
