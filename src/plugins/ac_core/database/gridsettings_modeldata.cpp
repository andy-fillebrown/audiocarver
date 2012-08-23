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

#include "gridsettings_modeldata.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <tools/scopeddatachange.h>

using namespace Ac;

namespace GridSettings {

ModelData::ModelData(IAggregate *aggregate)
    :   Base::ModelData(aggregate)
    ,   _snapEnabled(DEFAULT_GRIDSETTINGS_SNAPENABLED)
    ,   _gridSnapEnabled(DEFAULT_GRIDSETTINGS_GRIDSNAPENABLED)
    ,   _timeSnap(DEFAULT_GRIDSETTINGS_TIMESNAP)
    ,   _pitchSnap(DEFAULT_GRIDSETTINGS_PITCHSNAP)
    ,   _controlSnap(DEFAULT_GRIDSETTINGS_CONTROLSNAP)
{}

IUnknown *ModelData::initialize()
{
    return Base::ModelData::initialize();
}

bool ModelData::setSnapEnabled(bool enabled)
{
    if (_snapEnabled == enabled)
        return false;
    ScopedDataChange data_change(this, SnapEnabledRole);
    _snapEnabled = enabled;
    return true;
}

bool ModelData::setGridSnapEnabled(bool enabled)
{
    if (_gridSnapEnabled == enabled)
        return false;
    ScopedDataChange data_change(this, GridSnapEnabledRole);
    _gridSnapEnabled = enabled;
    return true;
}

bool ModelData::setTimeSnap(qreal snap)
{
    snap = qMax(qreal(0.0f), snap);
    if (_timeSnap == snap)
        return false;
    ScopedDataChange data_change(this, TimeSnapRole);
    _timeSnap = snap;
    return true;
}

bool ModelData::setPitchSnap(qreal snap)
{
    snap = qMax(qreal(0.0f), snap);
    if (_pitchSnap == snap)
        return false;
    ScopedDataChange data_change(this, PitchSnapRole);
    _pitchSnap = snap;
    return true;
}

bool ModelData::setControlSnap(qreal snap)
{
    snap = qMax(qreal(0.0f), snap);
    if (_controlSnap == snap)
        return false;
    ScopedDataChange data_change(this, ControlSnapRole);
    _controlSnap = snap;
    return true;
}

int ModelData::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return SnapEnabledRole;
    case 1:
        return GridSnapEnabledRole;
    case 2:
        return TimeSnapRole;
    case 3:
        return PitchSnapRole;
    case 4:
        return ControlSnapRole;
    default:
        return Base::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case SnapEnabledRole:
        return isSnapEnabled();
    case GridSnapEnabledRole:
        return isGridSnapEnabled();
    case TimeSnapRole:
        return timeSnap();
    case PitchSnapRole:
        return pitchSnap();
    case ControlSnapRole:
        return controlSnap();
    default:
        return Base::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case SnapEnabledRole:
        return setSnapEnabled(qvariant_cast<bool>(value));
    case GridSnapEnabledRole:
        return setGridSnapEnabled(qvariant_cast<bool>(value));
    case TimeSnapRole:
        return setTimeSnap(qvariant_cast<qreal>(value));
    case PitchSnapRole:
        return setPitchSnap(qvariant_cast<qreal>(value));
    case ControlSnapRole:
        return setControlSnap(qvariant_cast<qreal>(value));
    default:
        return Base::ModelData::setValue(value, role);
    }
}

}
