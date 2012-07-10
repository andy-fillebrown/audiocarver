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

#include "ac_database_projectsettings.h"

#include <mi_scopeddatachange.h>

namespace Core {

IAggregator *ProjectSettings::init()
{
    return Object::init();
}

bool ProjectSettings::setSampleRate(int rate)
{
    rate = qMax(44100, rate);
    if (_sampleRate == rate)
        return false;
    ScopedDataChange data_change(this, Ac::SampleRateRole);
    _sampleRate = rate;
    return true;
}

bool ProjectSettings::setControlRate(int rate)
{
    rate = qMax(1, rate);
    if (_controlRate == rate)
        return false;
    ScopedDataChange data_change(this, Ac::ControlRateRole);
    _controlRate = rate;
    return true;
}

bool ProjectSettings::setCurveRate(int rate)
{
    rate = qMax(1, rate);
    if (_curveRate == rate)
        return false;
    ScopedDataChange data_change(this, Ac::CurveRateRole);
    _curveRate = rate;
    return true;
}

IAggregate *ProjectSettings::ModelData::init()
{
    return Object::ModelData::init();
}

IAggregate *ProjectSettings::ModelItem::init()
{
    return Object::ModelItem::init();
}

} // namespace Core
