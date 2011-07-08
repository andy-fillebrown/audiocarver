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
#include <ac_scenemanager.h>
#include <ac_score.h>
#include <ac_timescene.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcGraphicsBarLineItemPrivate : public AcGraphicsGridLineItemData
{
public:
    AcGraphicsBarLineItemPrivate()
    {
        AcTimeScene::instance()->addItem(labelItem);
    }

    void updateLocation()
    {
        const qreal location = gridLine->location();
        const AcScore *score = AcScore::instance();
        const qreal scale = score->viewSettings()->scaleX();
        const QRect labelRect = AcSceneManager::instance()->fontMetrics().boundingRect(gridLine->label());
        const qreal x = (location * scale) - (labelRect.width() / 2);
        const qreal y = AcTimeScene::instance()->height();
        scoreLineItem->setLine(location, 0.0f, location, 127.0f);
        labelItem->setPos(x, y);
    }
};

} // namespace Private

AcGraphicsBarLineItem::AcGraphicsBarLineItem(AcBarLine *barLine, QObject *parent)
    :   AcGraphicsGridLineItem(*(new AcGraphicsBarLineItemPrivate), parent)
{
    setGridLine(barLine);
}

AcGraphicsBarLineItem::~AcGraphicsBarLineItem()
{}

void AcGraphicsBarLineItem::setGridLine(AcGridLine *gridLine)
{
    Q_D(AcGraphicsBarLineItem);
    AcGraphicsGridLineItem::setGridLine(gridLine);
    if (gridLine)
        d->updateLocation();
}

void AcGraphicsBarLineItem::updateViewSettingsProperty(const QString &propertyName)
{
    Q_D(AcGraphicsBarLineItem);
    if ("scaleX" == propertyName)
        d->updateLocation();
}

void AcGraphicsBarLineItem::updateGridLineProperty(const QString &propertyName)
{
    Q_D(AcGraphicsBarLineItem);
    AcGraphicsGridLineItem::updateGridLineProperty(propertyName);
    if ("location" == propertyName)
        d->updateLocation();
}
