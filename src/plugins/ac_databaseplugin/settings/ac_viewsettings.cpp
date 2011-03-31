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

#include "ac_viewsettings.h"

using namespace Private;

namespace Private {

class AcViewSettingsData
{
public:
    qreal posX;
    qreal posY;
    qreal scaleX;
    qreal scaleY;

    AcViewSettingsData()
        :   posX(0.0f)
        ,   posY(0.0f)
        ,   scaleX(1.0f)
        ,   scaleY(1.0f)
    {}
};

} // namespace Private

AcViewSettings::AcViewSettings(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcViewSettingsData)
{}

AcViewSettings::~AcViewSettings()
{
    delete d;
}

qreal AcViewSettings::positionX() const
{
    return d->posX;
}

void AcViewSettings::setPositionX(qreal positionX)
{
    if (d->posX == positionX)
        return;
    d->posX = positionX;
    emit propertyChanged(propertyIndex("positionX"));
}

qreal AcViewSettings::positionY() const
{
    return d->posY;
}

void AcViewSettings::setPositionY(qreal positionY)
{
    if (d->posY == positionY)
        return;
    d->posY = positionY;
    emit propertyChanged(propertyIndex("positionY"));
}

qreal AcViewSettings::scaleX() const
{
    return d->scaleX;
}

void AcViewSettings::setScaleX(qreal scaleX)
{
    scaleX = qBound(0.125, scaleX, 1000.0);
    if (d->scaleX == scaleX)
        return;
    d->scaleX = scaleX;
    emit propertyChanged(propertyIndex("scaleX"));
}

qreal AcViewSettings::scaleY() const
{
    return d->scaleY;
}

void AcViewSettings::setScaleY(qreal scaleY)
{
    scaleY = qBound(0.125, scaleY, 1000.0);
    if (d->scaleY == scaleY)
        return;
    d->scaleY = scaleY;
    emit propertyChanged(propertyIndex("scaleY"));
}
