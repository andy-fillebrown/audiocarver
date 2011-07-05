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
#include <ac_tuningline.h>

using namespace Private;

namespace Private {

class AcGraphicsTuningLineItemData
{
public:
    AcGraphicsTuningLineItem *q;

};

} // namespace Private

AcGraphicsTuningLineItem::AcGraphicsTuningLineItem(AcTuningLine *tuningLine)
    :   AcGraphicsGridLineItem(tuningLine)
{}

AcGraphicsTuningLineItem::~AcGraphicsTuningLineItem()
{}

//void AcTuningItem::updateItems()
//{
//    AcGuidelineItem::updateItems();
//    QGraphicsLineItem *lineItem = qLineItem();
//    const qreal length = AcScore::instance()->length();
//    AcGuideline *guideline = this->guideline();
//    const qreal location = guideline->location();
//    lineItem->setLine(0.0f, location, length, 0.0f);
//    QGraphicsTextItem *textItem = qTextItem();
//    const QFontMetrics &fontMetrics = AcScoreScene::instance()->fontMetrics();
//    QRect textRect = fontMetrics.boundingRect(guideline->text());
//    qreal scaleY = AcScore::instance()->viewSettings()->scaleY();
//    textItem->setPos(20.0f - textRect.width(), ((127.0f - location) * scaleY) - (textRect.height() / 1.5));
//}
