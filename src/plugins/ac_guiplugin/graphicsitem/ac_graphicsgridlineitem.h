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

class AcGraphicsGridLineItemPrivate : public AcGraphicsItemPrivate
{
public:
    QGraphicsLineItem *lineItem;
    QGraphicsTextItem *labelItem;

    AcGraphicsGridLineItemPrivate();
    virtual ~AcGraphicsGridLineItemPrivate();

    const AcGridLine *gridLine() const;

    void update();
    void updateFont();
    void updateLabel();
    void updateColor();
};

class AcGraphicsGridLineItem : public AcGraphicsItem
{
    Q_OBJECT

public:
    virtual ~AcGraphicsGridLineItem()
    {}

    int priority() const;
    QRectF labelRect() const;

protected slots:
    virtual void updateFontSettings(int i);
    virtual void updateViewSettings(int i) = 0;

protected:
    AcGraphicsGridLineItem(AcGraphicsGridLineItemPrivate &dd, QObject *parent = 0);
    virtual void updateDataObject(int i);

private:
    Q_DISABLE_COPY(AcGraphicsGridLineItem)
    Q_DECLARE_PRIVATE(AcGraphicsGridLineItem)
};

#endif // AC_GRAPHICSGRIDLINEITEM_H
