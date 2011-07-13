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

#include "ac_graphicsvaluelineitem.h"
#include <ac_score.h>
#include <ac_valueline.h>
#include <ac_viewsettings.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcGraphicsValueLineItemPrivate : public AcGraphicsGridLineItemData
{
public:

    AcGraphicsValueLineItemPrivate(AcValueLine *valueLine)
    {
        databaseObject = valueLine;
        update();
    }

    void update()
    {
        updateLineGeometry();
        updateLabelPosition();
    }

    void updateLineGeometry()
    {
        const qreal pos = 1.0f - gridLine()->location();
        lineItem->setLine(0.0f, pos, score()->length(), pos);
    }

    void updateLabelPosition()
    {
        const AcGridLine *gridLine = this->gridLine();
        const qreal pos = 1.0f - gridLine->location();
        const qreal scale = score()->viewSettings()->valueScale();
        const QRect labelRect = fontMetrics().boundingRect(gridLine->label());
        const qreal x = valueScene()->width() - labelRect.width();
        const qreal y = (pos * scale) - (labelRect.height() / 1.25f);
        labelItem->setPos(x, y);
    }
};

} // namespace Private

AcGraphicsValueLineItem::AcGraphicsValueLineItem(AcValueLine *valueLine, QObject *parent)
    :   AcGraphicsGridLineItem(*(new AcGraphicsValueLineItemPrivate(valueLine)), parent)
{
    Q_D(AcGraphicsValueLineItem);
    connect(d->score(), SIGNAL(propertyChanged(int)), SLOT(updateScoreProperty(int)));
}

AcGraphicsValueLineItem::~AcGraphicsValueLineItem()
{}

QGraphicsItem *AcGraphicsValueLineItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsValueLineItem);
    switch (sceneType) {
    case ControlScene:
        return d->lineItem;
    case ValueScene:
        return d->labelItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsValueLineItem::updateViewSettingsProperty(int propertyIndex)
{
    if (AcViewSettings::ValueScale == propertyIndex) {
        Q_D(AcGraphicsValueLineItem);
        d->updateLabelPosition();
    }
}

void AcGraphicsValueLineItem::updateDatabaseObjectProperty(int propertyIndex)
{
    AcGraphicsGridLineItem::updateDatabaseObjectProperty(propertyIndex);
    if (AcValueLine::Location == propertyIndex) {
        Q_D(AcGraphicsValueLineItem);
        d->update();
    }
}

void AcGraphicsValueLineItem::updateScoreProperty(int propertyIndex)
{
    if (AcScore::Length == propertyIndex) {
        Q_D(AcGraphicsValueLineItem);
        d->updateLineGeometry();
    }
}
