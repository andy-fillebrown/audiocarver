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

#include "ac_graphicspitchlineitem.h"
#include <ac_gridline.h>
#include <ac_score.h>
#include <ac_viewsettings.h>
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class AcGraphicsPitchLineItemPrivate : public AcGraphicsGridLineItemPrivate
{
public:
    AcGraphicsPitchLineItemPrivate(AcGridLine *gridLine)
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
        const qreal pos = 127.0f - gridLine()->location();
        lineItem->setLine(0.0f, pos, AcScore::instance()->length(), pos);
    }

    void updateLabelPosition()
    {
        const AcGridLine *gridLine = this->gridLine();
        const qreal pos = 127.0f - gridLine->location();
        const qreal scale = score()->viewSettings()->pitchScale();
        const QRect labelRect = fontMetrics().boundingRect(gridLine->label());
        const qreal x = pitchLabelScene()->width() - labelRect.width();
        const qreal y = (pos * scale) - (labelRect.height() / 1.25f);
        labelItem->setPos(x, y);
    }
};

AcGraphicsPitchLineItem::AcGraphicsPitchLineItem(AcGridLine *gridLine, QObject *parent)
    :   AcGraphicsGridLineItem(*(new AcGraphicsPitchLineItemPrivate(gridLine)), parent)
{
    Q_CONNECT(AcScore::instance(), SIGNAL(changed(int)), this, SLOT(updateScore(int)));
}

AcGraphicsPitchLineItem::~AcGraphicsPitchLineItem()
{}

QGraphicsItem *AcGraphicsPitchLineItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsPitchLineItem);
    switch (sceneType) {
    case PitchScene:
        return d->lineItem;
    case PitchLabelScene:
        return d->labelItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsPitchLineItem::updateViewSettings(int i)
{
    if (AcViewSettings::PitchScaleIndex == i) {
        Q_D(AcGraphicsPitchLineItem);
        d->updateLabelPosition();
    }
}

void AcGraphicsPitchLineItem::updateDataObject(int i)
{
    AcGraphicsGridLineItem::updateDataObject(i);
    if (AcGridLine::LocationIndex == i) {
        Q_D(AcGraphicsPitchLineItem);
        d->update();
    }
}

void AcGraphicsPitchLineItem::updateScore(int i)
{
    if (AcScore::LengthIndex == i) {
        Q_D(AcGraphicsPitchLineItem);
        d->updateLineGeometry();
    }
}
