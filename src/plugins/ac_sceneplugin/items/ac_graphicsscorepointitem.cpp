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

#include "ac_graphicsscorepointitem.h"
#include <ac_point.h>
#include <QGraphicsEllipseItem>

using namespace Private;

namespace Private {

class AcGraphicsScorePointItemPrivate : public AcGraphicsPointItemData
{
public:
    void update()
    {
        updateRect();
    }

    void updateRect()
    {
        const AcPoint *point = this->point();
        pointItem->setRect(point->x(), 127.0f - point->y(), 1.0f, 1.0f);
    }
};

} // namespace Private

AcGraphicsScorePointItem::AcGraphicsScorePointItem(AcPoint *point, QObject *parent)
    :   AcGraphicsPointItem(point, parent)
{
    Q_D(AcGraphicsScorePointItem);
    d->update();
}

AcGraphicsScorePointItem::~AcGraphicsScorePointItem()
{}

QGraphicsItem *AcGraphicsScorePointItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsScorePointItem);
    switch (sceneType) {
    case ScoreScene:
        return d->pointItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsScorePointItem::updateDatabaseObjectProperty(const QString &propertyName)
{
    if ("x" == propertyName || "y" == propertyName) {
        Q_D(AcGraphicsScorePointItem);
        d->updateRect();
    }
}
