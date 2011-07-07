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

class AcGraphicsBarLineItemData
{
public:
    AcGraphicsBarLineItem *q;
    QGraphicsTextItem *labelItem;

    AcGraphicsBarLineItemData(AcGraphicsBarLineItem *q)
        :   q(q)
        ,   labelItem(new QGraphicsTextItem)
    {
        AcTimeScene::instance()->addItem(labelItem);
    }

    ~AcGraphicsBarLineItemData()
    {
        delete labelItem;
    }

    void update()
    {
        updateFont();
        updateLocation();
        updateLabel();
    }

    void updateFont()
    {
        MiFont *font = AcScore::instance()->fontSettings();
        labelItem->setFont(QFont(font->family(), font->pointSize()));
    }

    void updateLocation()
    {
        const AcGridLine *gridLine = q->gridLine();
        const qreal location = gridLine->location();
        const AcScore *score = AcScore::instance();
        const qreal scale = score->viewSettings()->scaleX();
        const QRect labelRect = AcSceneManager::instance()->fontMetrics().boundingRect(gridLine->label());
        const qreal x = (location * scale) - (labelRect.width() / 2);
        const qreal y = AcTimeScene::instance()->height();
        labelItem->setPos(x, y);
    }

    void updateLabel()
    {
        labelItem->setPlainText(q->gridLine()->label());
    }

    void show()
    {
        labelItem->show();
    }

    void hide()
    {
        labelItem->hide();
    }
};

} // namespace Private

AcGraphicsBarLineItem::AcGraphicsBarLineItem(AcBarLine *barLine, QObject *parent)
    :   AcGraphicsGridLineItem(barLine, parent)
    ,   d(new AcGraphicsBarLineItemData(this))
{
    setGridLine(barLine);
}

AcGraphicsBarLineItem::~AcGraphicsBarLineItem()
{
    delete d;
}

void AcGraphicsBarLineItem::setGridLine(AcGridLine *gridLine)
{
    AcGraphicsGridLineItem::setGridLine(gridLine);
    if (gridLine) {
        d->update();
        d->show();
    } else
        d->hide();
}

void AcGraphicsBarLineItem::updateFontSettingsProperty(const QString &propertyName)
{
    d->updateFont();
}

void AcGraphicsBarLineItem::updateViewSettingsProperty(const QString &propertyName)
{
    if ("scaleX" == propertyName)
        d->updateLocation();
}

void AcGraphicsBarLineItem::updateGridLineProperty(const QString &propertyName)
{
    AcGraphicsGridLineItem::updateGridLineProperty(propertyName);
    if ("location" == propertyName)
        d->updateLocation();
    else if ("label" == propertyName)
        d->updateLabel();
}
