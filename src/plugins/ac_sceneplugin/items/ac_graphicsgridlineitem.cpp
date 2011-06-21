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
#include <QGraphicsLineItem>

using namespace Private;

namespace Private {

class AcGraphicsGridLineItemData
{
public:
    AcGridLine *gridLine;
    QGraphicsLineItem *scoreLineItem;

    AcGraphicsGridLineItemData()
        :   gridLine(0)
        ,   scoreLineItem(new QGraphicsLineItem)
    {}

    ~AcGraphicsGridLineItemData()
    {
        delete scoreLineItem;
    }

    void updateItems()
    {
        scoreLineItem->setPen(gridLine->color());
    }

    void hideItems()
    {
        scoreLineItem->hide();
    }

    void showItems()
    {
        scoreLineItem->show();
    }
};

} // namespace Private

AcGraphicsGridLineItem::AcGraphicsGridLineItem(AcGridLine *gridLine)
    :   d(new AcGraphicsGridLineItemData)
{
    setGridLine(gridLine);
}

AcGraphicsGridLineItem::~AcGraphicsGridLineItem()
{
    delete d;
}

AcGridLine *AcGraphicsGridLineItem::gridLine() const
{
    return d->gridLine;
}

void AcGraphicsGridLineItem::setGridLine(AcGridLine *gridLine)
{
    if (d->gridLine == gridLine)
        return;
    d->gridLine = gridLine;
    if (gridLine) {
        d->updateItems();
        d->showItems();
    } else
        d->hideItems();
}

qreal AcGraphicsGridLineItem::location() const
{
    return d->gridLine->location();
}

const QColor &AcGraphicsGridLineItem::color() const
{
    return d->gridLine->color();
}

const QString &AcGraphicsGridLineItem::label() const
{
    return d->gridLine->label();
}

int AcGraphicsGridLineItem::priority() const
{
    return d->gridLine->priority();
}

QGraphicsLineItem *AcGraphicsGridLineItem::qGraphicsScoreLineItem() const
{
    return d->scoreLineItem;
}

QGraphicsLineItem *AcGraphicsGridLineItem::qGraphicsControllerLineItem() const
{
    return 0;
}
