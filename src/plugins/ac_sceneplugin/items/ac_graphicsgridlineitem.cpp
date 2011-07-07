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

class AcGraphicsGridLineItemData
{
public:
    AcGridLine *gridLine;
    QGraphicsLineItem *scoreLineItem;

    AcGraphicsGridLineItemData()
        :   gridLine(0)
        ,   scoreLineItem(new QGraphicsLineItem)
    {
        AcScoreScene::instance()->addItem(scoreLineItem);
    }

    void update()
    {
        updateLocation();
        updateColor();
    }

    void updateLocation()
    {
        scoreLineItem->setLine(gridLine->location(), 0.0f, gridLine->location(), 127.0f);
    }

    void updateColor()
    {
        scoreLineItem->setPen(gridLine->color());
    }

    void show()
    {
        scoreLineItem->show();
    }

    void hide()
    {
        scoreLineItem->hide();
    }
};

} // namespace Private

AcGraphicsGridLineItem::AcGraphicsGridLineItem(AcGridLine *gridLine, QObject *parent)
    :   QObject(parent)
    ,   d(new AcGraphicsGridLineItemData)
{
    AcScore *score = AcScore::instance();
    connect(score->fontSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateFontSettingsProperty(QString)));
    connect(score->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
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
    if (d->gridLine) {
        d->gridLine->disconnect(this);
    }
    d->gridLine = gridLine;
    if (d->gridLine) {
        connect(d->gridLine, SIGNAL(propertyChanged(QString)), SLOT(updateGridLineProperty(QString)));
        d->update();
        d->show();
    } else
        d->hide();
}

void AcGraphicsGridLineItem::updateGridLineProperty(const QString &propertyName)
{
    if ("location" == propertyName)
        d->updateLocation();
    else if ("color" == propertyName)
        d->updateColor();
}
