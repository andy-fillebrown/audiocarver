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

class QGraphicsLineItem;
class QGraphicsTextItem;
class QColor;
class QRectF;

class AcGraphicsGridLineItemPrivate;
class AcGraphicsGridLineItem : public AcGraphicsItem
{
    Q_OBJECT

public:
    ~AcGraphicsGridLineItem()
    {}

    int priority() const;
    void setPriority(int priority);

    QRectF labelRect() const;

    void updateDataObject(int i, const QVariant &value);

public slots:
    virtual void updateFontSettings();
    virtual void updateViewSettings(int i) = 0;

protected:
    inline AcGraphicsGridLineItem(AcGraphicsGridLineItemPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(AcGraphicsGridLineItem)
    Q_DECLARE_PRIVATE(AcGraphicsGridLineItem)
};

class AcGraphicsGridLineItemPrivate : public AcGraphicsItemPrivate
{
    Q_DECLARE_PUBLIC(AcGraphicsGridLineItem)

public:
    int priority;
    QGraphicsLineItem *lineItem;
    QGraphicsTextItem *labelItem;

    AcGraphicsGridLineItemPrivate(AcGraphicsGridLineItem *q);
    ~AcGraphicsGridLineItemPrivate();

    void updateFont();
    void updateLabel(const QString &label);
    void updateColor(const QColor &color);
};

inline AcGraphicsGridLineItem::AcGraphicsGridLineItem(AcGraphicsGridLineItemPrivate &dd, QObject *parent)
    :   AcGraphicsItem(dd, parent)
{}

#endif // AC_GRAPHICSGRIDLINEITEM_H
