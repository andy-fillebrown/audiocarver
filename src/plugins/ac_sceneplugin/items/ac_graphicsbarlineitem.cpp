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
//#include <ac_score.h>
//#include <ac_scorescene.h>
//#include <ac_viewsettings.h>
//#include <QGraphicsLineItem>
//#include <QGraphicsTextItem>

AcGraphicsBarLineItem::AcGraphicsBarLineItem(AcBarLine *barLine)
    :   AcGraphicsGridLineItem(barLine)
{}

AcGraphicsBarLineItem::~AcGraphicsBarLineItem()
{}

//void AcBarlineItem::updateItems()
//{
//    AcGuidelineItem::updateItems();
//    QGraphicsLineItem *lineItem = qLineItem();
//    AcGuideline *guideline = this->guideline();
//    const qreal location = guideline->location();
//    lineItem->setLine(location, 0.0f, location, 127.0f);
//    QGraphicsTextItem *textItem = qTextItem();
//    const QFontMetrics &fontMetrics = AcScoreScene::instance()->fontMetrics();
//    QRect textRect = fontMetrics.boundingRect(guideline->text());
//    qreal scaleX = AcScore::instance()->viewSettings()->scaleX();
//    textItem->setPos((location * scaleX) - (textRect.width() / 2), 10.0f);
//}
