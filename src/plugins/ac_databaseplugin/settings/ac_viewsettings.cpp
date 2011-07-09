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
    qreal timePosition;
    qreal pitchPosition;
    qreal valuePosition;
    qreal timeScale;
    qreal pitchScale;
    qreal valueScale;

    AcViewSettingsData()
        :   timePosition(0.0f)
        ,   pitchPosition(0.0f)
        ,   valuePosition(0.0f)
        ,   timeScale(1.0f)
        ,   pitchScale(1.0f)
        ,   valueScale(100.0f)
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

qreal AcViewSettings::timePosition() const
{
    return d->timePosition;
}

void AcViewSettings::setTimePosition(qreal position)
{
    if (d->timePosition == position)
        return;
    d->timePosition = position;
    emit propertyChanged("timePosition");
}

qreal AcViewSettings::pitchPosition() const
{
    return d->pitchPosition;
}

void AcViewSettings::setPitchPosition(qreal position)
{
    if (d->pitchPosition == position)
        return;
    d->pitchPosition = position;
    emit propertyChanged("pitchPosition");
}

qreal AcViewSettings::valuePosition() const
{
    return d->valuePosition;
}

void AcViewSettings::setValuePosition(qreal position)
{
    if (d->valuePosition == position)
        return;
    d->valuePosition = position;
    emit propertyChanged("valuePosition");
}

qreal AcViewSettings::timeScale() const
{
    return d->timeScale;
}

void AcViewSettings::setTimeScale(qreal scale)
{
    scale = qBound(0.125, scale, 1000.0);
    if (d->timeScale == scale)
        return;
    d->timeScale = scale;
    emit propertyChanged("timeScale");
}

qreal AcViewSettings::pitchScale() const
{
    return d->pitchScale;
}

void AcViewSettings::setPitchScale(qreal scale)
{
    scale = qBound(0.125, scale, 1000.0);
    if (d->pitchScale == scale)
        return;
    d->pitchScale = scale;
    emit propertyChanged("pitchScale");
}

qreal AcViewSettings::valueScale() const
{
    return d->valueScale;
}

void AcViewSettings::setValueScale(qreal scale)
{
    scale = qBound(0.125, scale, 1000.0);
    if (d->valueScale == scale)
        return;
    d->valueScale = scale;
    emit propertyChanged("valueScale");
}
