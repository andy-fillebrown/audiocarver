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
#include <QColor>
#include <QFont>
#include <QGraphicsLineItem>

using namespace Private;

namespace Private {

AcGraphicsGridLineItemData::AcGraphicsGridLineItemData()
    :   lineItem(new QGraphicsLineItem)
    ,   labelItem(new QGraphicsTextItem)
{}

AcGraphicsGridLineItemData::~AcGraphicsGridLineItemData()
{
    delete labelItem;
    delete lineItem;
}

const AcGridLine *AcGraphicsGridLineItemData::gridLine() const
{
    return qobject_cast<AcGridLine*>(databaseObject);
}

class AcGraphicsGridLineItemPrivate : public AcGraphicsGridLineItemData
{
public:
    void update()
    {
        updateFont();
        updateLabel();
        updateColor();
    }

    void updateFont()
    {
        labelItem->setFont(font());
    }

    void updateLabel()
    {
        labelItem->setPlainText(gridLine()->label());
    }

    void updateColor()
    {
        lineItem->setPen(QPen(gridLine()->color()));
    }
};

} // namespace Private

AcGraphicsGridLineItem::AcGraphicsGridLineItem(Private::AcGraphicsGridLineItemData &dd, QObject *parent)
    :   AcGraphicsItem(dd, parent)
{
    Q_D(AcGraphicsGridLineItem);
    const AcScore *score = d->score();
    connect(score->fontSettings(), SIGNAL(propertyChanged(int)), SLOT(updateFontSettingsProperty(int)));
    connect(score->viewSettings(), SIGNAL(propertyChanged(int)), SLOT(updateViewSettingsProperty(int)));
    d->update();
}

AcGraphicsGridLineItem::~AcGraphicsGridLineItem()
{}

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

void AcGraphicsGridLineItem::updateFontSettingsProperty(int propertyIndex)
{
    Q_UNUSED(propertyIndex);
    Q_D(AcGraphicsGridLineItem);
    d->updateFont();
}

void AcGraphicsGridLineItem::updateDatabaseObjectProperty(int propertyIndex)
{
    Q_D(AcGraphicsGridLineItem);
    switch (propertyIndex) {
    case AcGridLine::Label:
        d->updateLabel();
        break;
    case AcGridLine::Color:
        d->updateColor();
        break;
    default:
        break;
    }
}
