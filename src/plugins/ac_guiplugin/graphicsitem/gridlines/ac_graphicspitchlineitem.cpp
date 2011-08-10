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
#include <ac_scenemanager.h>
#include <ac_propertyindexes.h>
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class AcGraphicsPitchLineItemPrivate : public AcGraphicsHGridLineItemPrivate
{
public:
    AcGraphicsPitchLineItemPrivate(AcGraphicsPitchLineItem *q)
        :   AcGraphicsHGridLineItemPrivate(q)
    {}

    void updateLineLocation(qreal location)
    {
        const qreal pos = 127.0f - location;
        lineItem->setLine(0.0f, pos, pitchScene()->width(), pos);
    }

    void updateLineLength()
    {
        const qreal pos = lineItem->line().p1().y();
        lineItem->setLine(0.0f, pos, pitchScene()->width(), pos);
    }

    void updateLabelPosition()
    {
        const qreal pos = lineItem->line().p1().y();
        const qreal scale = sceneManager()->pitchScale();
        const QRect labelRect = fontMetrics().boundingRect(labelItem->toPlainText());
        const qreal x = pitchLabelScene()->width() - labelRect.width();
        const qreal y = (pos * scale) - (labelRect.height() / 1.25f);
        labelItem->setPos(x, y);
    }
};

AcGraphicsPitchLineItem::AcGraphicsPitchLineItem(QObject *parent)
    :   AcGraphicsHGridLineItem(*(new AcGraphicsPitchLineItemPrivate(this)), parent)
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
    if (ViewSettings::PitchScale == i) {
        Q_D(AcGraphicsPitchLineItem);
        d->updateLabelPosition();
    }
}

void AcGraphicsPitchLineItem::updateDataObject(int i, const QVariant &value)
{
    AcGraphicsGridLineItem::updateDataObject(i, value);
    if (GridLine::Location == i) {
        Q_D(AcGraphicsPitchLineItem);
        d->updateLineLocation(value.toReal());
        d->updateLabelPosition();
    }
}

void AcGraphicsPitchLineItem::updateScore(int i)
{
    if (Score::Length == i) {
        Q_D(AcGraphicsPitchLineItem);
        d->updateLineLength();
    }
}
