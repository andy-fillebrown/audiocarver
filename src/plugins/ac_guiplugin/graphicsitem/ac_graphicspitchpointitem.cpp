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
#include <ac_point.h>
#include <ac_viewsettings.h>
#include <QGraphicsRectItem>

class AcGraphicsPitchPointItemPrivate : public AcGraphicsPointItemPrivate
{
public:
    void update()
    {
        updateRect();
    }

    void updateRect()
    {
        const AcPoint *point = this->point();
        const qreal w = 6.0f;
        const qreal h = 6.0f;
        const qreal x = (viewSettings()->timeScale() * point->x()) - (w / 2.0f);
        const qreal y = (viewSettings()->pitchScale() * (127.0f - point->y())) - (h / 2.0f);
        pointItem->setRect(x, y, w, h);
    }
};

AcGraphicsPitchPointItem::AcGraphicsPitchPointItem(AcPoint *point, QObject *parent)
    :   AcGraphicsPointItem(point, parent)
{
    Q_D(AcGraphicsPitchPointItem);
    d->update();
}

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

void AcGraphicsPitchPointItem::updateViewSettings(int i)
{
    Q_D(AcGraphicsPitchPointItem);
    switch (i) {
    case AcViewSettings::TimeScaleIndex:
    case AcViewSettings::PitchScaleIndex:
        d->updateRect();
        break;
    default:
        break;
    }
}

void AcGraphicsPitchPointItem::updateDataObject(int i)
{
    Q_D(AcGraphicsPitchPointItem);
    switch (i) {
    case AcPoint::XIndex:
    case AcPoint::YIndex:
        d->updateRect();
        break;
    default:
        break;
    }
}
