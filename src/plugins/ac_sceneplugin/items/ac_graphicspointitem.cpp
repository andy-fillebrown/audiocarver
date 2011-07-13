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

#include "ac_graphicspointitem.h"
#include <ac_point.h>
#include <QBrush>
#include <QGraphicsRectItem>

using namespace Private;

namespace Private {

AcGraphicsPointItemData::AcGraphicsPointItemData(AcPoint *point)
    :   pointItem(new QGraphicsRectItem)
{
    databaseObject = point;
    pointItem->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
}

AcGraphicsPointItemData::~AcGraphicsPointItemData()
{
    delete pointItem;
}

const AcPoint *AcGraphicsPointItemData::point() const
{
    return qobject_cast<AcPoint*>(databaseObject);
}

class AcGraphicsPointItemPrivate : public AcGraphicsPointItemData
{};

} // namespace Private

AcGraphicsPointItem::AcGraphicsPointItem(AcPoint *point, QObject *parent)
    :   AcScaledGraphicsItem(*(new AcGraphicsPointItemData(point)), parent)
{}

AcGraphicsPointItem::~AcGraphicsPointItem()
{}

void AcGraphicsPointItem::updateViewSettingsProperty(int propertyIndex)
{
    Q_UNUSED(propertyIndex);
}
