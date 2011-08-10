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

#include "ac_graphicspitchpointitem.h"
#include <ac_scenemanager.h>
#include <ac_propertyindexes.h>
#include <QGraphicsRectItem>

class AcGraphicsPitchPointItemPrivate : public AcGraphicsPointItemPrivate
{
    Q_DECLARE_PUBLIC(AcGraphicsPitchPointItem)

public:
    AcGraphicsPitchPointItemPrivate(AcGraphicsPitchPointItem *q)
        :   AcGraphicsPointItemPrivate(q)
    {}

    ~AcGraphicsPitchPointItemPrivate()
    {}

    void updatePitchScale(qreal scale)
    {
        pointItem->setRect(pointItem->rect().x(), (scale * point.y()) - 3.0f, 6.0f, 6.0f);
    }
};

AcGraphicsPitchPointItem::AcGraphicsPitchPointItem(QObject *parent)
    :   AcGraphicsPointItem(*(new AcGraphicsPitchPointItemPrivate(this)), parent)
{}

QGraphicsItem *AcGraphicsPitchPointItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsPitchPointItem);
    switch (sceneType) {
    case PitchScene:
        return d->pointItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsPitchPointItem::updateDataObject(int i, const QVariant &value)
{
    Q_D(AcGraphicsPitchPointItem);
    switch (i) {
    case Point::Y:
        d->point.setY(127.0f - value.toReal());
    case Point::X:
        d->updateTimeScale(d->sceneManager()->timeScale());
        d->updatePitchScale(d->sceneManager()->pitchScale());
        break;
    default:
        break;
    }
}

void AcGraphicsPitchPointItem::updateViewSettings(int i, const QVariant &value)
{
    AcGraphicsPointItem::updateViewSettings(i, value);
    if (ViewSettings::PitchScale == i) {
        Q_D(AcGraphicsPitchPointItem);
        d->updatePitchScale(value.toReal());
    }
}
