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

#include "ac_graphicstimelineitem.h"
#include <ac_gridline.h>
#include <ac_score.h>
#include <ac_viewsettings.h>
#include <QColor>
#include <QFontMetrics>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>

class AcGraphicsTimeLineItemPrivate : public AcGraphicsGridLineItemPrivate
{
public:
    QGraphicsLineItem *volumeLineItem;

    AcGraphicsTimeLineItemPrivate(AcGridLine *gridLine)
        :   volumeLineItem(new QGraphicsLineItem)
    {
        dataObject = gridLine;
        update();
    }

    ~AcGraphicsTimeLineItemPrivate()
    {
        delete volumeLineItem;
    }

    void update()
    {
        updateColor();
        updateLocation();
    }

    void updateColor()
    {
        volumeLineItem->setPen(QPen(QColor(QRgb(gridLine()->color()))));
    }

    void updateLocation()
    {
        const AcGridLine *gridLine = this->gridLine();
        const qreal location = gridLine->location();
        lineItem->setLine(location, 0.0f, location, 127.0f);
        volumeLineItem->setLine(location, 0.0f, location, 1.0f);
        const qreal scale = score()->viewSettings()->timeScale();
        const QRect labelRect = fontMetrics().boundingRect(gridLine->label());
        const qreal x = (location * scale) - (labelRect.width() / 2.0f);
        const qreal y = (timeLabelScene()->height() / 2.0f) - (labelRect.height() / 2.0f);
        labelItem->setPos(x, y);
    }
};

AcGraphicsTimeLineItem::AcGraphicsTimeLineItem(AcGridLine *gridLine, QObject *parent)
    :   AcGraphicsGridLineItem(*(new AcGraphicsTimeLineItemPrivate(gridLine)), parent)
{}

AcGraphicsTimeLineItem::~AcGraphicsTimeLineItem()
{}

QGraphicsItem *AcGraphicsTimeLineItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsTimeLineItem);
    switch (sceneType) {
    case PitchScene:
        return d->lineItem;
    case VolumeScene:
        return d->volumeLineItem;
    case TimeLabelScene:
        return d->labelItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsTimeLineItem::updateViewSettings(int i, const QVariant &value)
{
    if (ViewSettings::TimeScale == i) {
        Q_D(AcGraphicsTimeLineItem);
        d->updateLocation();
    }
}

void AcGraphicsTimeLineItem::updateDataObject(int i, const QVariant &value)
{
    Q_D(AcGraphicsTimeLineItem);
    AcGraphicsGridLineItem::updateDataObject(i, value);
    switch (i) {
    case GridLine::Color:
        d->updateColor();
        break;
    case GridLine::Location:
        d->updateLocation();
        break;
    default:
        break;
    }
}
