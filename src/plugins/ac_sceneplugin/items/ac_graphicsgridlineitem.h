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

#ifndef AC_GRAPHICSGRIDLINEITEM_H
#define AC_GRAPHICSGRIDLINEITEM_H

#include <ac_graphicsitem.h>

class AcGridLine;
class QGraphicsLineItem;
class QGraphicsTextItem;
class QRectF;

namespace Private {

class AcGraphicsGridLineItemData : public AcGraphicsItemData
{
public:
    QGraphicsLineItem *lineItem;
    QGraphicsTextItem *labelItem;

    AcGraphicsGridLineItemData();
    virtual ~AcGraphicsGridLineItemData();

    const AcGridLine *gridLine();
    const AcGridLine *gridLine() const;
};

class AcGraphicsGridLineItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsGridLineItem : public AcGraphicsItem
{
    Q_OBJECT

protected:
    AcGraphicsGridLineItem(Private::AcGraphicsGridLineItemData &dd, QObject *parent = 0);

public:
    virtual ~AcGraphicsGridLineItem();

    int priority() const;
    QRectF labelRect() const;

protected slots:
    virtual void updateFontSettingsProperty(const QString &propertyName);
    virtual void updateViewSettingsProperty(const QString &propertyName) = 0;

protected:
    virtual void updateDatabaseObjectProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsGridLineItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsGridLineItem)
};

#endif // AC_GRAPHICSGRIDLINEITEM_H
