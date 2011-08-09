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

#include "ac_graphicsgridlineitem.h"
#include <ac_propertyindexes.h>
#include <QColor>
#include <QFont>
#include <QGraphicsLineItem>
#include <QPen>

int AcGraphicsGridLineItem::priority() const
{
    Q_D(const AcGraphicsGridLineItem);
    return d->priority;
}

void AcGraphicsGridLineItem::setPriority(int priority)
{
    Q_D(AcGraphicsGridLineItem);
    if (d->priority == priority)
        return;
    d->priority = priority;
}

QRectF AcGraphicsGridLineItem::labelRect() const
{
    Q_D(const AcGraphicsGridLineItem);
    return QRectF(d->labelItem->pos(), d->labelItem->boundingRect().size());
}

void AcGraphicsGridLineItem::updateFontSettings()
{
    Q_D(AcGraphicsGridLineItem);
    d->updateFont();
}

void AcGraphicsGridLineItem::updateDataObject(int i, const QVariant &value)
{
    Q_D(AcGraphicsGridLineItem);
    switch (i) {
    case GridLine::Label:
        d->updateLabel(value.toString());
        break;
    case GridLine::Color:
        d->updateColor(QRgb(value.value<quint32>()));
        break;
    default:
        break;
    }
}

AcGraphicsGridLineItemPrivate::AcGraphicsGridLineItemPrivate(AcGraphicsGridLineItem *q)
    :   AcGraphicsItemPrivate(q)
    ,   lineItem(new QGraphicsLineItem)
    ,   labelItem(new QGraphicsTextItem)
{}

AcGraphicsGridLineItemPrivate::~AcGraphicsGridLineItemPrivate()
{
    delete labelItem;
    delete lineItem;
}

void AcGraphicsGridLineItemPrivate::updateFont()
{
    labelItem->setFont(font());
}

void AcGraphicsGridLineItemPrivate::updateLabel(const QString &label)
{
    labelItem->setPlainText(label);
}

void AcGraphicsGridLineItemPrivate::updateColor(const QColor &color)
{
    lineItem->setPen(QPen(color));
}
