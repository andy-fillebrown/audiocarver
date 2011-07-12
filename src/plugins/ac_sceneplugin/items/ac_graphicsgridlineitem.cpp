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
#include <QPen>

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

const AcGridLine *AcGraphicsGridLineItemData::gridLine()
{
    return qobject_cast<AcGridLine*>(databaseObject);
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
        MiFont *font = AcScore::instance()->fontSettings();
        labelItem->setFont(QFont(font->family(), font->pointSize()));
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
    AcScore *score = AcScore::instance();
    connect(score->fontSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateFontSettingsProperty(QString)));
    connect(score->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
    Q_D(AcGraphicsGridLineItem);
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

void AcGraphicsGridLineItem::updateFontSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
    Q_D(AcGraphicsGridLineItem);
    d->updateFont();
}

void AcGraphicsGridLineItem::updateDatabaseObjectProperty(const QString &propertyName)
{
    Q_D(AcGraphicsGridLineItem);
    if ("label" == propertyName)
        d->updateLabel();
    else if ("color" == propertyName)
        d->updateColor();
}
