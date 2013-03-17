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

#include "ac_gui_curve_graphicsdelegate.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
#include <igraphicssubentityitem.h>
#include <igripdata.h>
#include <igriplistdata.h>
#include <imodeldata.h>

using namespace Ac;

namespace Curve {

static IGripListData *findGripListData(GraphicsDelegate *this_gdelegate)
{
    IGripListData *griplist_gdata = 0;
    IGraphicsSubEntityItem *this_gitem = QUERY(IGraphicsSubEntityItem, this_gdelegate);
    QList<IGraphicsItem*> subentities = this_gitem->subentities();
    foreach (IGraphicsItem *subentity, subentities) {
        griplist_gdata = QUERY(IGripListData, subentity);
        if (griplist_gdata)
            return griplist_gdata;
    }
    return 0;
}

static PointList buildPointList(GraphicsDelegate *this_gdelegate)
{
    PointList points;
    IGripListData *griplist_gdata = findGripListData(this_gdelegate);
    QList<IGripData*> grips = griplist_gdata->grips();
    foreach (IGripData *grip, grips)
        points.append(Point(grip->position(), CurveType(grip->curveType())));
    return points;
}

void GraphicsDelegate::updateModel()
{
    IModelData *curve_data = QUERY(IModelData, this);
    curve_data->set(QVariant::fromValue(buildPointList(this)), PointsRole);
}

void GraphicsDelegate::updateGraphics()
{
    IGraphicsData *curve_gdata = QUERY(IGraphicsData, this);
    curve_gdata->update(PointsRole, QVariant::fromValue(buildPointList(this)));
}

}
