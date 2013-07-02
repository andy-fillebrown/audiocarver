/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_core_projectsettings_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace ProjectSettings {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Object::ModelItem(aggregate)
    ,   _sampleRate(DEFAULT_PROJECTSETTINGS_SAMPLERATE)
    ,   _controlRate(DEFAULT_PROJECTSETTINGS_CONTROLRATE)
    ,   _curveRate(DEFAULT_PROJECTSETTINGS_CURVERATE)
{}

int ModelItem::itemType() const
{
    return ProjectSettingsItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ProjectSettingsItem == itemType;
}

int ModelItem::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return InstrumentDirectoryRole;
    case 1:
        return SampleRateRole;
    case 2:
        return ControlRateRole;
    case 3:
        return CurveRateRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case InstrumentDirectoryRole:
        return _instrumentDirectory;
    case SampleRateRole:
        return _sampleRate;
    case ControlRateRole:
        return _controlRate;
    case CurveRateRole:
        return _curveRate;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case InstrumentDirectoryRole: {
        const QString dir = qvariant_cast<QString>(value);
        if (_instrumentDirectory == dir)
            return false;
        ScopedDataChange data_change(this, InstrumentDirectoryRole);
        _instrumentDirectory = dir;
        return true;
    }
    case SampleRateRole: {
        const int rate = qMax(44100, qvariant_cast<int>(value));
        if (_sampleRate == rate)
            return false;
        ScopedDataChange data_change(this, SampleRateRole);
        _sampleRate = rate;
        return true;
    }
    case ControlRateRole: {
        const int rate = qMax(1, qvariant_cast<int>(value));
        if (_controlRate == rate)
            return false;
        ScopedDataChange data_change(this, ControlRateRole);
        _controlRate = rate;
        return true;
    }
    case CurveRateRole: {
        const int rate = qMax(1, qvariant_cast<int>(value));
        if (_curveRate == rate)
            return false;
        ScopedDataChange data_change(this, CurveRateRole);
        _curveRate = rate;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
