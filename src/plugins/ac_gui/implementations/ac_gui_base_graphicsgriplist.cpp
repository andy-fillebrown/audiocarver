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

#include "ac_gui_base_graphicsgriplist.h"
#include <ac_core_point.h>
#include <iaggregate.h>
#include <igraphicsgrip.h>

using namespace Ac;

namespace Base {

void *GraphicsGripList::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

GraphicsGripList::GraphicsGripList(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    _aggregate->appendComponent(this);
}

QList<Point> GraphicsGripList::points() const
{
    QList<IGraphicsGrip*> grips = this->grips();
    PointList points;
    foreach (IGraphicsGrip *grip, grips)
        points.append(Point(grip->position(), CurveType(grip->curveType())));
    return points;
}

}
