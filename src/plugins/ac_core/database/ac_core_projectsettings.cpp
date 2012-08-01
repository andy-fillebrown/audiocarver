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

#include "ac_core_projectsettings.h"

#include <mi_core_scopeddatachange.h>

using namespace Mi::Core;

namespace Ac {
namespace Core {

IAggregator *ProjectSettings::init()
{
    return DataObject::init();
}

bool ProjectSettings::setSampleRate(int rate)
{
    rate = qMax(44100, rate);
    if (_sampleRate == rate)
        return false;
    ScopedDataChange data_change(this, SampleRateRole);
    _sampleRate = rate;
    return true;
}

bool ProjectSettings::setControlRate(int rate)
{
    rate = qMax(1, rate);
    if (_controlRate == rate)
        return false;
    ScopedDataChange data_change(this, ControlRateRole);
    _controlRate = rate;
    return true;
}

bool ProjectSettings::setCurveRate(int rate)
{
    rate = qMax(1, rate);
    if (_curveRate == rate)
        return false;
    ScopedDataChange data_change(this, CurveRateRole);
    _curveRate = rate;
    return true;
}

IAggregate *ProjectSettings::ModelData::init()
{
    return DataObject::ModelData::init();
}

IAggregate *ProjectSettings::ModelItem::init()
{
    return DataObject::ModelItem::init();
}

} // namespace Core
} // namespace Ac
