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

#include "ac_guidelineitem.h"
//#include <ac_guideline.h>
//#include <ac_score.h>
//#include <ac_viewsettings.h>
//#include <mi_font.h>
//#include <QFont>
//#include <QGraphicsLineItem>
//#include <QGraphicsTextItem>

//using namespace Private;

//namespace Private {

//class AcGuidelineItemData
//{
//public:
//    AcGuideline *guideline;
//    QGraphicsLineItem *lineItem;
//    QGraphicsTextItem *textItem;

//    AcGuidelineItemData()
//        :   guideline(0)
//        ,   lineItem(new QGraphicsLineItem)
//        ,   textItem(new QGraphicsTextItem)
//    {}

//    ~AcGuidelineItemData()
//    {
//        delete textItem;
//        delete lineItem;
//    }

//    void updateItems()
//    {
//        if (guideline) {
//            lineItem->setPen(guideline->color());
//            lineItem->show();
//            MiFont *font = AcScore::instance()->fontSettings();
//            textItem->setFont(QFont(font->family(), font->pointSize()));
//            textItem->setPlainText(guideline->text());
//            textItem->show();
//        } else {
//            lineItem->hide();
//            textItem->hide();
//        }
//    }
//};

//} // namespace Private

//AcGuidelineItem::AcGuidelineItem(AcGuideline *guideline)
//    :   d(new AcGuidelineItemData)
//{
//    setGuideline(guideline);
//    AcScore *score = AcScore::instance();
//    MiFont *font = score->fontSettings();
//    AcViewSettings *viewSettings = score->viewSettings();
//    connect(score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
//    connect(font, SIGNAL(propertyChanged(QString)), SLOT(updateFontSettingsProperty(QString)));
//    connect(viewSettings, SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
//}

//AcGuidelineItem::~AcGuidelineItem()
//{
//    delete d;
//}

//AcGuideline *AcGuidelineItem::guideline() const
//{
//    return d->guideline;
//}

//void AcGuidelineItem::setGuideline(AcGuideline *guideline)
//{
//    if (d->guideline == guideline)
//        return;
//    if (d->guideline)
//        d->guideline->disconnect(this);
//    d->guideline = guideline;
//    d->updateItems();
//    if (guideline)
//        connect(guideline, SIGNAL(propertyChanged(QString)), SLOT(updateGuideline(QString)));
//}

//int AcGuidelineItem::priority() const
//{
//    return d->guideline->priority();
//}

//QGraphicsLineItem *AcGuidelineItem::qLineItem() const
//{
//    return d->lineItem;
//}

//QGraphicsTextItem *AcGuidelineItem::qTextItem() const
//{
//    return d->textItem;
//}

//void AcGuidelineItem::updateScoreProperty(const QString &propertyName)
//{
//    if ("length" == propertyName)
//        updateLength();
//}

//void AcGuidelineItem::updateFontSettingsProperty(const QString &propertyName)
//{
//    if ("family" == propertyName)
//        updateFontFamily();
//    else if ("pointSize" == propertyName)
//        updateFontPointSize();
//}

//void AcGuidelineItem::updateViewSettingsProperty(const QString &propertyName)
//{
//    if ("scaleX" == propertyName)
//        updateScaleX();
//    else if ("scaleY" == propertyName)
//        updateScaleY();
//}

//void AcGuidelineItem::updateGuideline(const QString &propertyName)
//{
//    if ("location" == propertyName)
//        updateLocation();
//    else if ("color" == propertyName)
//        updateColor();
//}

//void AcGuidelineItem::updateLength()
//{}

//void AcGuidelineItem::updateFontFamily()
//{}

//void AcGuidelineItem::updateFontPointSize()
//{}

//void AcGuidelineItem::updateScaleX()
//{}

//void AcGuidelineItem::updateScaleY()
//{}

//void AcGuidelineItem::updateLocation()
//{}

//void AcGuidelineItem::updateColor()
//{}
