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

#include "ac_graphicsbarlineitem.h"
#include <ac_barline.h>
#include <ac_score.h>
#include <ac_viewsettings.h>
#include <QColor>
#include <QFontMetrics>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcGraphicsBarLineItemPrivate : public AcGraphicsGridLineItemData
{
public:
    QGraphicsLineItem *controlLineItem;

    AcGraphicsBarLineItemPrivate(AcBarLine *barLine)
        :   controlLineItem(new QGraphicsLineItem)
    {
        databaseObject = barLine;
        update();
    }

    ~AcGraphicsBarLineItemPrivate()
    {
        delete controlLineItem;
    }

    void update()
    {
        updateColor();
        updateLocation();
    }

    void updateColor()
    {
        controlLineItem->setPen(gridLine()->color());
    }

    void updateLocation()
    {
        const AcGridLine *gridLine = this->gridLine();
        const qreal location = gridLine->location();
        lineItem->setLine(location, 0.0f, location, 127.0f);
        controlLineItem->setLine(location, 0.0f, location, 1.0f);
        const qreal scale = score()->viewSettings()->timeScale();
        const QRect labelRect = fontMetrics().boundingRect(gridLine->label());
        const qreal x = (location * scale) - (labelRect.width() / 2.0f);
        const qreal y = (timeScene()->height() / 2.0f) - (labelRect.height() / 2.0f);
        labelItem->setPos(x, y);
    }
};

} // namespace Private

AcGraphicsBarLineItem::AcGraphicsBarLineItem(AcBarLine *barLine, QObject *parent)
    :   AcGraphicsGridLineItem(*(new AcGraphicsBarLineItemPrivate(barLine)), parent)
{}

AcGraphicsBarLineItem::~AcGraphicsBarLineItem()
{}

QGraphicsItem *AcGraphicsBarLineItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsBarLineItem);
    switch (sceneType) {
    case ScoreScene:
        return d->lineItem;
    case ControlScene:
        return d->controlLineItem;
    case TimeScene:
        return d->labelItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsBarLineItem::updateViewSettingsProperty(int propertyIndex)
{
    if (AcViewSettings::TimeScale == propertyIndex) {
        Q_D(AcGraphicsBarLineItem);
        d->updateLocation();
    }
}

void AcGraphicsBarLineItem::updateDatabaseObjectProperty(int propertyIndex)
{
    Q_D(AcGraphicsBarLineItem);
    AcGraphicsGridLineItem::updateDatabaseObjectProperty(propertyIndex);
    switch (propertyIndex) {
    case AcBarLine::Color:
        d->updateColor();
        break;
    case AcBarLine::Location:
        d->updateLocation();
        break;
    default:
        break;
    }
}
