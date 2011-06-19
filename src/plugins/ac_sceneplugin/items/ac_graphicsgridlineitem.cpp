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
#include <mi_font.h>
#include <QFont>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcGraphicsGridLineItemData
{
public:
    AcGridLine *gridLine;
    QGraphicsLineItem *lineItem;
    QGraphicsTextItem *textItem;

    AcGraphicsGridLineItemData()
        :   gridLine(0)
        ,   lineItem(new QGraphicsLineItem)
        ,   textItem(new QGraphicsTextItem)
    {}

    ~AcGraphicsGridLineItemData()
    {
        delete textItem;
        delete lineItem;
    }

    void updateItems()
    {
        if (gridLine) {
            lineItem->setPen(gridLine->color());
            lineItem->show();
            MiFont *font = AcScore::instance()->fontSettings();
            textItem->setFont(QFont(font->family(), font->pointSize()));
            textItem->setPlainText(gridLine->text());
            textItem->show();
        } else {
            lineItem->hide();
            textItem->hide();
        }
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
    d->updateItems();
}

int AcGraphicsGridLineItem::priority() const
{
    return d->gridLine->priority();
}

QGraphicsLineItem *AcGraphicsGridLineItem::qGraphicsLineItem() const
{
    return d->lineItem;
}

QGraphicsTextItem *AcGraphicsGridLineItem::qGraphicsTextItem() const
{
    return d->textItem;
}
