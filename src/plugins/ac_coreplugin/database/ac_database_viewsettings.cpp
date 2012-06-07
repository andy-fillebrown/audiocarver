/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_database_viewsettings.h"

#include <ac_database_score.h>

#include <mi_scopeddatachange.h>

namespace Database {

IAggregator *ViewSettings::init()
{
    return this;
}

bool ViewSettings::setTimePosition(qreal position)
{
    position = qBound(qreal(0.0f), position, Score::instance()->length());
    if (_timePosition == position)
        return false;
    ScopedDataChange data_change(this, Ac::TimePositionRole);
    _timePosition = position;
    return true;
}

bool ViewSettings::setPitchPosition(qreal position)
{
    position = qBound(qreal(0.0f), position, qreal(127.0f));
    if (_pitchPosition == position)
        return false;
    ScopedDataChange data_change(this, Ac::PitchPositionRole);
    _pitchPosition = position;
    return true;
}

bool ViewSettings::setControlPosition(qreal position)
{
    position = qBound(qreal(0.0f), position, qreal(1.0f));
    if (_controlPosition == position)
        return false;
    ScopedDataChange data_change(this, Ac::ControlPositionRole);
    _controlPosition = position;
    return true;
}

bool ViewSettings::setTimeScale(qreal scale)
{
    scale = qBound(VIEWSCALE_MIN, scale, VIEWSCALE_MAX);
    if (_timeScale == scale)
        return false;
    ScopedDataChange data_change(this, Ac::TimeScaleRole);
    _timeScale = scale;
    return true;
}

bool ViewSettings::setPitchScale(qreal scale)
{
    scale = qBound(VIEWSCALE_MIN, scale, VIEWSCALE_MAX);
    if (_pitchScale == scale)
        return false;
    ScopedDataChange data_change(this, Ac::PitchScaleRole);
    _pitchScale = scale;
    return true;
}

bool ViewSettings::setControlScale(qreal scale)
{
    scale = qBound(VIEWSCALE_MIN, scale, VIEWSCALE_MAX);
    if (_controlScale == scale)
        return false;
    ScopedDataChange data_change(this, Ac::ControlScaleRole);
    _controlScale = scale;
    return true;
}

} // namespace Database
