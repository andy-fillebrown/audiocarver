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

#include "ac_graphicstuninglineitem.h"
#include <ac_pitchscene.h>
#include <ac_scenemanager.h>
#include <ac_score.h>
#include <ac_tuningline.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcGraphicsTuningLineItemData
{
public:
    AcGraphicsTuningLineItem *q;
    QGraphicsTextItem *labelItem;

    AcGraphicsTuningLineItemData(AcGraphicsTuningLineItem *q)
        :   q(q)
        ,   labelItem(new QGraphicsTextItem)
    {
        AcPitchScene::instance()->addItem(labelItem);
    }

    ~AcGraphicsTuningLineItemData()
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
        const qreal scale = score->viewSettings()->scaleY();
        const QRect labelRect = AcSceneManager::instance()->fontMetrics().boundingRect(gridLine->label());
        const qreal x = AcPitchScene::instance()->width() - labelRect.width();
        const qreal y = ((127.0f - location) * scale) - (labelRect.height() / 1.5);
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

AcGraphicsTuningLineItem::AcGraphicsTuningLineItem(AcTuningLine *tuningLine)
    :   AcGraphicsGridLineItem(tuningLine)
    ,   d(new AcGraphicsTuningLineItemData(this))
{
    setGridLine(tuningLine);
}

AcGraphicsTuningLineItem::~AcGraphicsTuningLineItem()
{
    delete d;
}

void AcGraphicsTuningLineItem::setGridLine(AcGridLine *gridLine)
{
    AcGraphicsGridLineItem::setGridLine(gridLine);
    if (gridLine) {
        d->update();
        d->show();
    } else
        d->hide();
}

void AcGraphicsTuningLineItem::updateFontSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
    d->updateFont();
}

void AcGraphicsTuningLineItem::updateViewSettingsProperty(const QString &propertyName)
{
    if ("scaleY" == propertyName)
        d->updateLocation();
}

void AcGraphicsTuningLineItem::updateGridLineProperty(const QString &propertyName)
{
    AcGraphicsGridLineItem::updateGridLineProperty(propertyName);
    if ("location" == propertyName)
        d->updateLocation();
    else if ("label" == propertyName)
        d->updateLabel();
}
