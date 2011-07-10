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
#include <ac_controlscene.h>
#include <ac_scenemanager.h>
#include <ac_score.h>
#include <ac_scorescene.h>
#include <ac_timescene.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcGraphicsBarLineItemPrivate : public AcGraphicsGridLineItemData
{
public:
    QGraphicsLineItem *controlLineItem;

    AcGraphicsBarLineItemPrivate()
        :   controlLineItem(new QGraphicsLineItem)
    {
        AcScoreScene::instance()->addItem(lineItem);
        AcControlScene::instance()->addItem(controlLineItem);
        AcTimeScene::instance()->addItem(labelItem);
    }

    void update()
    {
        updateColor();
        updateLocation();
    }

    void updateColor()
    {
        controlLineItem->setPen(gridLine->color());
    }

    void updateLocation()
    {
        const qreal location = gridLine->location();
        lineItem->setLine(location, 0.0f, location, 127.0f);
        controlLineItem->setLine(location, 0.0f, location, 1.0f);
        const AcScore *score = AcScore::instance();
        const qreal scale = score->viewSettings()->timeScale();
        const QRect labelRect = AcSceneManager::instance()->fontMetrics().boundingRect(gridLine->label());
        const qreal x = (location * scale) - (labelRect.width() / 2.0f);
        const qreal y = (AcTimeScene::instance()->height() / 2.0f) - (labelRect.height() / 2.0f);
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

void AcGraphicsBarLineItem::show()
{
    Q_D(AcGraphicsBarLineItem);
    AcGraphicsGridLineItem::show();
    d->controlLineItem->show();
}

void AcGraphicsBarLineItem::hide()
{
    Q_D(AcGraphicsBarLineItem);
    AcGraphicsGridLineItem::hide();
    d->controlLineItem->hide();
}

void AcGraphicsBarLineItem::setGridLine(AcGridLine *gridLine)
{
    Q_D(AcGraphicsBarLineItem);
    AcGraphicsGridLineItem::setGridLine(gridLine);
    if (gridLine)
        d->update();
}

void AcGraphicsBarLineItem::updateViewSettingsProperty(const QString &propertyName)
{
    Q_D(AcGraphicsBarLineItem);
    if ("timeScale" == propertyName)
        d->updateLocation();
}

void AcGraphicsBarLineItem::updateGridLineProperty(const QString &propertyName)
{
    Q_D(AcGraphicsBarLineItem);
    AcGraphicsGridLineItem::updateGridLineProperty(propertyName);
    if ("color" == propertyName)
        d->updateColor();
    else if ("location" == propertyName)
        d->updateLocation();
}
