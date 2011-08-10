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
#include <ac_propertyindexes.h>
#include <ac_scenemanager.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class AcGraphicsVolumeLineItemPrivate : public AcGraphicsHGridLineItemPrivate
{
public:

    AcGraphicsVolumeLineItemPrivate(AcGraphicsVolumeLineItem *q)
        :   AcGraphicsHGridLineItemPrivate(q)
    {}

    void updateLineLocation(qreal location)
    {
        const qreal pos = 1.0f - location;
        lineItem->setLine(0.0f, pos, volumeScene()->width(), pos);
    }

    void updateLineLength()
    {
        const qreal pos = lineItem->line().p1().y();
        lineItem->setLine(0.0f, pos, volumeScene()->width(), pos);
    }

    void updateLabelPosition()
    {
        const qreal pos = lineItem->line().p1().y();
        const qreal scale = sceneManager()->volumeScale();
        const QRect labelRect = fontMetrics().boundingRect(labelItem->toPlainText());
        const qreal x = volumeLabelScene()->width() - labelRect.width();
        const qreal y = (pos * scale) - (labelRect.height() / 1.25f);
        labelItem->setPos(x, y);
    }
};

AcGraphicsVolumeLineItem::AcGraphicsVolumeLineItem(QObject *parent)
    :   AcGraphicsHGridLineItem(*(new AcGraphicsVolumeLineItemPrivate(this)), parent)
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

void AcGraphicsVolumeLineItem::updateDataObject(int i, const QVariant &value)
{
    AcGraphicsGridLineItem::updateDataObject(i, value);
    if (GridLine::Location == i) {
        Q_D(AcGraphicsVolumeLineItem);
        d->updateLineLocation(value.toReal());
        d->updateLabelPosition();
    }
}

void AcGraphicsVolumeLineItem::updateViewSettings(int i)
{
    if (ViewSettings::VolumeScale == i) {
        Q_D(AcGraphicsVolumeLineItem);
        d->updateLabelPosition();
    }
}

void AcGraphicsVolumeLineItem::updateScore(int i)
{
    if (Score::Length == i) {
        Q_D(AcGraphicsVolumeLineItem);
        d->updateLineLength();
    }
}
