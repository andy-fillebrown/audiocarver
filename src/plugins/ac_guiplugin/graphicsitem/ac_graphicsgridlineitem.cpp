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
#include <ac_gridline.h>
#include <ac_score.h>
#include <ac_viewsettings.h>
#include <mi_fontsettings.h>
#include <QColor>
#include <QFont>
#include <QGraphicsLineItem>
#include <QPen>

AcGraphicsGridLineItemPrivate::AcGraphicsGridLineItemPrivate()
    :   lineItem(new QGraphicsLineItem)
    ,   labelItem(new QGraphicsTextItem)
{}

AcGraphicsGridLineItemPrivate::~AcGraphicsGridLineItemPrivate()
{
    delete labelItem;
    delete lineItem;
}

const AcGridLine *AcGraphicsGridLineItemPrivate::gridLine() const
{
    return dataObject->cast<AcGridLine>();
}

void AcGraphicsGridLineItemPrivate::update()
{
    updateFont();
    updateLabel();
    updateColor();
}

void AcGraphicsGridLineItemPrivate::updateFont()
{
    labelItem->setFont(font());
}

void AcGraphicsGridLineItemPrivate::updateLabel()
{
    labelItem->setPlainText(gridLine()->label());
}

void AcGraphicsGridLineItemPrivate::updateColor()
{
    lineItem->setPen(QPen(QColor(QRgb(gridLine()->color()))));
}

int AcGraphicsGridLineItem::priority() const
{
    Q_D(const AcGraphicsGridLineItem);
    return d->gridLine()->priority();
}

QRectF AcGraphicsGridLineItem::labelRect() const
{
    Q_D(const AcGraphicsGridLineItem);
    return QRectF(d->labelItem->pos(), d->labelItem->boundingRect().size());
}

void AcGraphicsGridLineItem::updateFontSettings(int i, const QVariant &value)
{
    Q_UNUSED(i);
    Q_D(AcGraphicsGridLineItem);
    d->updateFont();
}

AcGraphicsGridLineItem::AcGraphicsGridLineItem(AcGraphicsGridLineItemPrivate &dd, QObject *parent)
    :   AcGraphicsItem(dd, parent)
{
    Q_D(AcGraphicsGridLineItem);
    const AcScore *score = d->score();
    Q_CONNECT(score->fontSettings(), SIGNAL(changed(int,QVariant)), this, SLOT(updateFontSettings(int,QVariant)));
    Q_CONNECT(score->viewSettings(), SIGNAL(changed(int,QVariant)), this, SLOT(updateViewSettings(int,QVariant)));
    d->update();
}

void AcGraphicsGridLineItem::updateDataObject(int i, const QVariant &value)
{
    Q_D(AcGraphicsGridLineItem);
    switch (i) {
    case GridLine::Label:
        d->updateLabel();
        break;
    case GridLine::Color:
        d->updateColor();
        break;
    default:
        break;
    }
}
