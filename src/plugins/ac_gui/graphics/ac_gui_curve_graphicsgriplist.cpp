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

#include "ac_gui_curve_graphicsgriplist.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
#include <iaggregate.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <igraphicsitem.h>
#include <igraphicsgrip.h>
#include <imodelitem.h>

using namespace Ac;

static bool gripLessThan(IGraphicsGrip *a, IGraphicsGrip *b)
{
    QPointF a_pos = a->position();
    QPointF b_pos = b->position();
    if (a_pos.x() < b_pos.x())
        return true;
    if (b_pos.x() < a_pos.x())
        return false;
    if (a_pos.y() < b_pos.y())
        return true;
    return false;
}

namespace Curve {

GraphicsGripList::~GraphicsGripList()
{
    foreach (IGraphicsGrip *grip, _grips)
        delete query<IAggregate>(grip);
    _grips.clear();
}

void GraphicsGripList::sort()
{
    qSort(_grips.begin(), _grips.end(), gripLessThan);
}

void GraphicsGripList::update(int role, const QVariant &value)
{
    if (PointsRole == role || OriginalPositionRole == role) {
        PointList points;
        if (value.isNull()) {
            IModelItem *this_item = query<IModelItem>(this);
            points = get<PointList>(this_item, PointsRole);
        }
        else
            points = qvariant_cast<PointList>(value);
        if (_grips.count() < points.count()) {
            IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
            while (_grips.count() < points.count()) {
                IAggregate *grip_aggregate = factory->create(GripItem, aggregate());
                IGraphicsGrip *grip = query<IGraphicsGrip>(grip_aggregate);
                _grips.append(grip);
            }
        }
        while (points.count() < _grips.count()) {
            delete _grips.last();
            _grips.removeLast();
        }
        int grip_update_role = PositionRole;
        if (OriginalPositionRole == role)
            grip_update_role = OriginalPositionRole;
        for (int i = 0;  i < _grips.count();  ++i) {
            IGraphicsGrip *grip = query<IGraphicsGrip>(_grips.at(i));
            const Point &point = points.at(i);
            grip->update(grip_update_role, point.pos);
            grip->update(CurveTypeRole, point.curveType);
        }
    } else
        Object::GraphicsGripList::update(role, value);
}

}
