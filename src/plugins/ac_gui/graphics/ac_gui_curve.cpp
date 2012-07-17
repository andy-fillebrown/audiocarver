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

#include "ac_gui_curve.h"

#include <mi_imodeldata.h>

namespace Ac {
namespace Gui {

IAggregator *Curve::init()
{
    return this;
}

IAggregate *Curve::Entity::init()
{
    _graphicsCurveItem = new GraphicsCurveItem;
    _graphicsCurveItem->setEntity(this);
    return this;
}

Curve::Entity::~Entity()
{
    delete _graphicsCurveItem;
}

void Curve::Entity::update(int role)
{
    switch (role) {
    case Ac::PointsRole:
        graphicsCurveItem()->setPoints(query<IModelData>(a())->get<PointList>(Ac::PointsRole));
    }
}

IAggregate *Curve::SubEntity::init()
{
    return this;
}

} // namespace Gui
} // namespace Ac
