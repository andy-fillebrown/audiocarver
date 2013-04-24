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

#include "ac_gui_velocity_graphicsgriplist.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>
#include <igraphicsgrip.h>
#include <igraphicsitem.h>
#include <imodelitem.h>

using namespace Ac;

namespace Velocity {

void GraphicsGripList::initialize()
{
    _grip = IDatabaseObjectFactory::instance()->create(GripItem, aggregate());
    Object::GraphicsGripList::initialize();
}

GraphicsGripList::~GraphicsGripList()
{
    qDelete(_grip);
}

QList<IGraphicsGrip*> GraphicsGripList::grips() const
{
    QList<IGraphicsGrip*> griplist;
    griplist.append(query<IGraphicsGrip>(_grip));
    return griplist;
}

void GraphicsGripList::update(int role, const QVariant &value)
{
    if (PointsRole == role || OriginalPositionRole == role) {
        Point point;
        if (value.isNull()) {
            IGraphicsItem *curve_gitem = query<IGraphicsItem>(this);
            IModelItem *note_item = query<IModelItem>(curve_gitem->parent());
            IModelItem *pitchcurve_item = query<IModelItem>(note_item->findItem(PitchCurveItem));
            PointList pitch_points = get<PointList>(pitchcurve_item, PointsRole);
            point.pos.setX(pitch_points.first().pos.x());
            point.pos.setY(get<qreal>(note_item, VolumeRole));
        } else {
            PointList points = qvariant_cast<PointList>(value);
            if (points.isEmpty())
                return;
            point = points.first();
        }
        int grip_update_role = PositionRole;
        if (OriginalPositionRole == role)
            grip_update_role = OriginalPositionRole;
        query<IGraphicsGrip>(_grip)->update(grip_update_role, point.pos);
    } else
        Object::GraphicsGripList::update(role, value);
}

}
