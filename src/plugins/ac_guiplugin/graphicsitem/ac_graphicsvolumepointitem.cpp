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

#include "ac_graphicsvolumepointitem.h"
#include <ac_point.h>
#include <QGraphicsEllipseItem>

class AcGraphicsVolumePointItemPrivate : public AcGraphicsPointItemPrivate
{};

AcGraphicsVolumePointItem::AcGraphicsVolumePointItem(AcPoint *point, QObject *parent)
    :   AcGraphicsPointItem(point, parent)
{}

QGraphicsItem *AcGraphicsVolumePointItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsVolumePointItem);
    switch (sceneType) {
    case VolumeScene:
        return d->pointItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsVolumePointItem::updateViewSettings(int i)
{
    Q_UNUSED(i);
}

void AcGraphicsVolumePointItem::updateDataObject(int i)
{
    Q_UNUSED(i);
}
