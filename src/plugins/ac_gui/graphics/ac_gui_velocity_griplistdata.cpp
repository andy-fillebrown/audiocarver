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

#include "ac_gui_velocity_griplistdata.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
#include <iaggregate.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <igraphicsdata.h>
#include <igraphicsitem.h>
#include <igraphicsiteminfo.h>
#include <igripdata.h>
#include <imodeldata.h>
#include <imodelitem.h>

using namespace Ac;

namespace Velocity {

GripListData::~GripListData()
{
    delete QUERY(IAggregate, _grip);
}

void GripListData::initialize()
{
    Object::GripListData::initialize();
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    IModelItem *this_item = QUERY(IModelItem, this);
    _grip = QUERY(IGripData, factory->create(GripItem, this_item));
    QGraphicsItem *grip_node = _grip->findNode();
    grip_node->setParentItem(findNode());
    grip_node->setData(0, quintptr(_grip));
}

void GripListData::update(int role, const QVariant &value)
{
    if (PointsRole == role
             || OriginalPositionRole == role) {
        Point point;
        if (value.isNull()) {
            IGraphicsItem *curve_gitem = QUERY(IGraphicsItem, this)->parent();
            IModelItem *note_item = QUERY(IModelItem, curve_gitem->parent());
            IModelData *pitchcurve_data = QUERY(IModelData, note_item->findItem(PitchCurveItem));
            IModelData *note_data = QUERY(IModelData, note_item);
            PointList pitch_points = pitchcurve_data->get<PointList>(PointsRole);
            point.pos.setX(pitch_points.first().pos.x());
            point.pos.setY(note_data->get<qreal>(VolumeRole));
        }
        else
            point = qvariant_cast<PointList>(value).first();
        int grip_update_role = PositionRole;
        if (OriginalPositionRole == role)
            grip_update_role = OriginalPositionRole;
        _grip->update(grip_update_role, point.pos);
    } else
        Object::GripListData::update(role, value);
}

}
