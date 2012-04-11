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

#include "ac_curve.h"

#include <ac_scoreobject.h>

Q_INIT_ROLES(Curve) {
    Ac::PointsRole
};

IAggregator *Curve::init()
{
    _graphicsCurveItem.reset(new GraphicsCurveItem);
    _graphicsCurveItem->setEntity(query<IEntity>(this));
    static PointList points;
    _pointsStack.push(points);
    return Base::init();
}

IAggregate *Curve::Entity::init()
{
    return this;
}

IAggregate *Curve::SubEntity::init()
{
    return this;
}

IAggregate *Curve::Points::init()
{
    return this;
}

IAggregate *Curve::ModelData::init()
{
    return Base::init();
}

void Curve::updateGraphicsItems()
{
    graphicsCurveItem()->setPoints(pointsStack().top());
    scoreObject()->updatePoints();
}

GraphicsParent *Curve::graphicsParent() const
{
    return scoreObject();
}
