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
#include <ac_scenemanager.h>
#include <ac_propertyindexes.h>
#include <QGraphicsRectItem>

class AcGraphicsVolumePointItemPrivate : public AcGraphicsPointItemPrivate
{
    Q_DECLARE_PUBLIC(AcGraphicsVolumePointItem)

public:
    AcGraphicsVolumePointItemPrivate(AcGraphicsVolumePointItem *q)
        :   AcGraphicsPointItemPrivate(q)
    {}

    ~AcGraphicsVolumePointItemPrivate()
    {}

    void updateVolumeScale(qreal scale)
    {
        pointItem->setRect(pointItem->rect().x(), (scale * point.y()) - 3.0f, 6.0f, 6.0f);
    }
};

AcGraphicsVolumePointItem::AcGraphicsVolumePointItem(QObject *parent)
    :   AcGraphicsPointItem(*(new AcGraphicsVolumePointItemPrivate(this)), parent)
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

void AcGraphicsVolumePointItem::updateDataObject(int i, const QVariant &value)
{
    Q_D(AcGraphicsVolumePointItem);
    switch (i) {
    case Point::Y:
        d->point.setY(1.0f - value.toReal());
    case Point::X:
        d->updateTimeScale(d->sceneManager()->timeScale());
        d->updateVolumeScale(d->sceneManager()->volumeScale());
        break;
    default:
        break;
    }
}

void AcGraphicsVolumePointItem::updateViewSettings(int i, const QVariant &value)
{
    AcGraphicsPointItem::updateViewSettings(i, value);
    if (ViewSettings::PitchScale == i) {
        Q_D(AcGraphicsVolumePointItem);
        d->updateVolumeScale(value.toReal());
    }
}
