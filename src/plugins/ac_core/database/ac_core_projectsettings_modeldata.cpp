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

#include "ac_core_projectsettings_modeldata.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace ProjectSettings {

ModelData::ModelData(IAggregate *aggregate)
    :   Base::ModelData(aggregate)
    ,   _sampleRate(DEFAULT_PROJECTSETTINGS_SAMPLERATE)
    ,   _controlRate(DEFAULT_PROJECTSETTINGS_CONTROLRATE)
    ,   _curveRate(DEFAULT_PROJECTSETTINGS_CURVERATE)
{}

IUnknown *ModelData::initialize()
{
    return Base::ModelData::initialize();
}

bool ModelData::setSampleRate(int rate)
{
    rate = qMax(44100, rate);
    if (_sampleRate == rate)
        return false;
    ScopedDataChange data_change(this, SampleRateRole);
    _sampleRate = rate;
    return true;
}

bool ModelData::setControlRate(int rate)
{
    rate = qMax(1, rate);
    if (_controlRate == rate)
        return false;
    ScopedDataChange data_change(this, ControlRateRole);
    _controlRate = rate;
    return true;
}

bool ModelData::setCurveRate(int rate)
{
    rate = qMax(1, rate);
    if (_curveRate == rate)
        return false;
    ScopedDataChange data_change(this, CurveRateRole);
    _curveRate = rate;
    return true;
}

int ModelData::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return SampleRateRole;
    case 1:
        return ControlRateRole;
    case 2:
        return CurveRateRole;
    default:
        return Base::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case SampleRateRole:
        return sampleRate();
    case ControlRateRole:
        return controlRate();
    case CurveRateRole:
        return curveRate();
    default:
        return Base::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case SampleRateRole:
        return setSampleRate(qvariant_cast<int>(value));
    case ControlRateRole:
        return setControlRate(qvariant_cast<int>(value));
    case CurveRateRole:
        return setCurveRate(qvariant_cast<int>(value));
    default:
        return Base::ModelData::setValue(value, role);
    }
}

}
