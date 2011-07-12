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
#include <ac_scorescene.h>
#include <ac_tuningline.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcGraphicsTuningLineItemPrivate : public AcGraphicsGridLineItemData
{
public:

    AcGraphicsTuningLineItemPrivate()
    {
        AcScoreScene::instance()->addItem(lineItem);
        AcPitchScene::instance()->addItem(labelItem);
    }

    void update()
    {
        updateLineGeometry();
        updateLabelPosition();
    }

    void updateLineGeometry()
    {
        const qreal pos = 127.0f - gridLine->location();
        lineItem->setLine(0.0f, pos, AcScore::instance()->length(), pos);
    }

    void updateLabelPosition()
    {
        const qreal pos = 127.0f - gridLine->location();
        const AcScore *score = AcScore::instance();
        const qreal scale = score->viewSettings()->pitchScale();
        const QRect labelRect = AcSceneManager::instance()->fontMetrics().boundingRect(gridLine->label());
        const qreal x = AcPitchScene::instance()->width() - labelRect.width();
        const qreal y = (pos * scale) - (labelRect.height() / 1.25f);
        labelItem->setPos(x, y);
    }
};

} // namespace Private

AcGraphicsTuningLineItem::AcGraphicsTuningLineItem(AcTuningLine *tuningLine, QObject *parent)
    :   AcGraphicsGridLineItem(*(new AcGraphicsTuningLineItemPrivate), parent)
{
    connect(AcScore::instance(), SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
    setDatabaseObject(tuningLine);
}

AcGraphicsTuningLineItem::~AcGraphicsTuningLineItem()
{}

void AcGraphicsTuningLineItem::setDatabaseObject(AcGridLine *gridLine)
{
    AcGraphicsGridLineItem::setDatabaseObject(gridLine);
    if (gridLine) {
        Q_D(AcGraphicsTuningLineItem);
        d->update();
    }
}

void AcGraphicsTuningLineItem::updateViewSettingsProperty(const QString &propertyName)
{
    if ("pitchScale" == propertyName) {
        Q_D(AcGraphicsTuningLineItem);
        d->updateLabelPosition();
    }
}

void AcGraphicsTuningLineItem::updateGridLineProperty(const QString &propertyName)
{
    AcGraphicsGridLineItem::updateGridLineProperty(propertyName);
    if ("location" == propertyName) {
        Q_D(AcGraphicsTuningLineItem);
        d->update();
    }
}

void AcGraphicsTuningLineItem::updateScoreProperty(const QString &propertyName)
{
    if ("length" == propertyName) {
        Q_D(AcGraphicsTuningLineItem);
        d->updateLineGeometry();
    }
}
