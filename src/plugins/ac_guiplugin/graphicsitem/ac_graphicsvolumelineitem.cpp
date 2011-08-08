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

#include "ac_graphicsvolumelineitem.h"
#include <ac_gridline.h>
#include <ac_score.h>
#include <ac_viewsettings.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class AcGraphicsVolumeLineItemPrivate : public AcGraphicsGridLineItemPrivate
{
public:

    AcGraphicsVolumeLineItemPrivate(AcGridLine *gridLine)
    {
        dataObject = gridLine;
        update();
    }

    void update()
    {
        updateLineGeometry();
        updateLabelPosition();
    }

    void updateLineGeometry()
    {
        const qreal pos = 1.0f - gridLine()->location();
        lineItem->setLine(0.0f, pos, score()->length(), pos);
    }

    void updateLabelPosition()
    {
        const AcGridLine *gridLine = this->gridLine();
        const qreal pos = 1.0f - gridLine->location();
        const qreal scale = score()->viewSettings()->volumeScale();
        const QRect labelRect = fontMetrics().boundingRect(gridLine->label());
        const qreal x = volumeLabelScene()->width() - labelRect.width();
        const qreal y = (pos * scale) - (labelRect.height() / 1.25f);
        labelItem->setPos(x, y);
    }
};

AcGraphicsVolumeLineItem::AcGraphicsVolumeLineItem(AcGridLine *gridLine, QObject *parent)
    :   AcGraphicsGridLineItem(*(new AcGraphicsVolumeLineItemPrivate(gridLine)), parent)
{
    Q_D(AcGraphicsVolumeLineItem);
    Q_CONNECT(d->score(), SIGNAL(changed(int)), this, SLOT(updateScore(int)));
}

AcGraphicsVolumeLineItem::~AcGraphicsVolumeLineItem()
{}

QGraphicsItem *AcGraphicsVolumeLineItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsVolumeLineItem);
    switch (sceneType) {
    case VolumeScene:
        return d->lineItem;
    case VolumeLabelScene:
        return d->labelItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsVolumeLineItem::updateViewSettings(int i, const QVariant &value)
{
    if (AcViewSettings::VolumeScaleIndex == i) {
        Q_D(AcGraphicsVolumeLineItem);
        d->updateLabelPosition();
    }
}

void AcGraphicsVolumeLineItem::updateDataObject(int i, const QVariant &value)
{
    AcGraphicsGridLineItem::updateDataObject(i, value);
    if (AcGridLine::LocationIndex == i) {
        Q_D(AcGraphicsVolumeLineItem);
        d->update();
    }
}

void AcGraphicsVolumeLineItem::updateScore(int i, const QVariant &value)
{
    if (AcScore::LengthIndex == i) {
        Q_D(AcGraphicsVolumeLineItem);
        d->updateLineGeometry();
    }
}
