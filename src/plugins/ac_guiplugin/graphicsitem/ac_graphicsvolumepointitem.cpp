/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "ac_graphicscontrolpointitem.h"
#include <ac_point.h>
#include <QGraphicsEllipseItem>

using namespace Private;

namespace Private {

class AcGraphicsControlPointItemPrivate : public AcGraphicsPointItemData
{};

} // namespace Private

AcGraphicsControlPointItem::AcGraphicsControlPointItem(AcPoint *point, QObject *parent)
    :   AcGraphicsPointItem(point, parent)
{}

AcGraphicsControlPointItem::~AcGraphicsControlPointItem()
{}

QGraphicsItem *AcGraphicsControlPointItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsControlPointItem);
    switch (sceneType) {
    case ControlScene:
        return d->pointItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsControlPointItem::updateDatabaseObjectProperty(int propertyIndex)
{
    Q_UNUSED(propertyIndex);
}
