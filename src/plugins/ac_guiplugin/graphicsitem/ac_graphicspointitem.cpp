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
#include <ac_propertyindexes.h>
#include <ac_scenemanager.h>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QPen>

AcGraphicsPointItemPrivate::AcGraphicsPointItemPrivate(AcGraphicsPointItem *q)
    :   AcScaledGraphicsItemPrivate(q)
    ,   curveType(Ac::NoCurve)
    ,   pointItem(new QGraphicsRectItem)
{
    pointItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    pointItem->setPen(QPen(Qt::blue));
    pointItem->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    pointItem->setZValue(1.0f);
    pointItem->setData(0, quintptr(q));
}

AcGraphicsPointItemPrivate::~AcGraphicsPointItemPrivate()
{
    delete pointItem;
}

void AcGraphicsPointItemPrivate::updateTimeScale(qreal scale)
{
    pointItem->setRect((scale * point.x()) - 3.0f, pointItem->rect().y(), 6.0f, 6.0f);
}

void AcGraphicsPointItem::updateDataObject(int i, const QVariant &value)
{
    Q_D(AcGraphicsPointItem);
    switch (i) {
    case CurvePoint::X:
        d->point.setX(value.toReal());
        break;
    case CurvePoint::Y:
        d->point.setY(127.0f - value.toReal());
        break;
    case CurvePoint::CurveType:
        d->curveType = Ac::CurveType(value.toInt());
        break;
    default:
        break;
    }
}

void AcGraphicsPointItem::updateViewSettings(int i, const QVariant &value)
{
    Q_D(AcGraphicsPointItem);
    if (ViewSettings::TimeScale == i)
        d->updateTimeScale(value.toReal());
}
