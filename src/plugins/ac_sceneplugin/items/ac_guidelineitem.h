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

#ifndef AC_GUIDELINEITEM_H
#define AC_GUIDELINEITEM_H

#include <QObject>
#include <ac_scene_global.h>

class AcGuideline;
class QGraphicsLineItem;
class QGraphicsTextItem;

namespace Private {

class AcGuidelineItemData;

} // namespace Private

class AC_SCENE_EXPORT AcGuidelineItem : public QObject
{
//    Q_OBJECT

//public:
//    AcGuidelineItem(AcGuideline *guideline = 0);
//    virtual ~AcGuidelineItem();

//    AcGuideline *guideline() const;
//    void setGuideline(AcGuideline *guideline);

//    int priority() const;

//    QGraphicsLineItem *qLineItem() const;
//    QGraphicsTextItem *qTextItem() const;

//public slots:
//    void updateScoreProperty(const QString &propertyName);
//    void updateFontSettingsProperty(const QString &propertyName);
//    void updateViewSettingsProperty(const QString &propertyName);
//    void updateGuideline(const QString &propertyName);
//    virtual void updateLength();
//    virtual void updateFontFamily();
//    virtual void updateFontPointSize();
//    virtual void updateScaleX();
//    virtual void updateScaleY();
//    virtual void updateLocation();
//    virtual void updateColor();

//private:
//    Q_DISABLE_COPY(AcGuidelineItem)
//    Private::AcGuidelineItemData *d;
};

#endif // AC_GUIDELINEITEM_H
