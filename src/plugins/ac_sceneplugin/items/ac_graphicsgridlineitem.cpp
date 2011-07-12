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
#include <ac_scorescene.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <QGraphicsLineItem>

using namespace Private;

namespace Private {

AcGraphicsGridLineItemData::AcGraphicsGridLineItemData()
    :   gridLine(0)
    ,   lineItem(new QGraphicsLineItem)
    ,   labelItem(new QGraphicsTextItem)
{}

AcGraphicsGridLineItemData::~AcGraphicsGridLineItemData()
{
    delete labelItem;
    delete lineItem;
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
        labelItem->setPlainText(gridLine->label());
    }

    void updateColor()
    {
        lineItem->setPen(gridLine->color());
    }
};

} // namespace Private

AcGraphicsGridLineItem::AcGraphicsGridLineItem(Private::AcGraphicsGridLineItemData &dd, QObject *parent)
    :   QObject(parent)
    ,   d_ptr(&dd)
{
    AcScore *score = AcScore::instance();
    connect(score->fontSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateFontSettingsProperty(QString)));
    connect(score->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
}

AcGraphicsGridLineItem::~AcGraphicsGridLineItem()
{
    delete d_ptr;
}

void AcGraphicsGridLineItem::setDatabaseObject(AcGridLine *gridLine)
{
    Q_D(Private::AcGraphicsGridLineItem);
    if (d->gridLine == gridLine)
        return;
    if (d->gridLine) {
        d->gridLine->disconnect(this);
    }
    d->gridLine = gridLine;
    if (d->gridLine) {
        connect(d->gridLine, SIGNAL(propertyChanged(QString)), SLOT(updateGridLineProperty(QString)));
        d->update();
    }
}

int AcGraphicsGridLineItem::priority() const
{
    Q_D(const AcGraphicsGridLineItem);
    return d->gridLine->priority();
}

QRectF AcGraphicsGridLineItem::labelRect() const
{
    Q_D(const AcGraphicsGridLineItem);
    return QRectF(d->labelItem->pos(), d->labelItem->boundingRect().size());
}

bool AcGraphicsGridLineItem::isVisible() const
{
    Q_D(const AcGraphicsGridLineItem);
    return d->lineItem->isVisible();
}

void AcGraphicsGridLineItem::show()
{
    Q_D(AcGraphicsGridLineItem);
    d->lineItem->show();
    d->labelItem->show();
}

void AcGraphicsGridLineItem::hide()
{
    Q_D(AcGraphicsGridLineItem);
    d->lineItem->hide();
    d->labelItem->hide();
}

void AcGraphicsGridLineItem::updateFontSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
    Q_D(AcGraphicsGridLineItem);
    d->updateFont();
}

void AcGraphicsGridLineItem::updateGridLineProperty(const QString &propertyName)
{
    Q_D(Private::AcGraphicsGridLineItem);
    if ("label" == propertyName)
        d->updateLabel();
    else if ("color" == propertyName)
        d->updateColor();
}
