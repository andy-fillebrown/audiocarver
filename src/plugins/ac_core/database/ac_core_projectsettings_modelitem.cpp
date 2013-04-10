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
#include "ac_core_namespace.h"
#include "ac_core_projectsettings_aggregate.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace ProjectSettings {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

int ModelItem::itemType() const
{
    return ProjectSettingsItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ProjectSettingsItem == itemType;
}

int ModelItem::roleCount() const
{
    return Aggregate::TotalRoleCount;
}

int ModelItem::roleAt(int i) const
{
    switch (i - Aggregate::RoleCountOffset) {
    case 0:
        return SampleRateRole;
    case 1:
        return ControlRateRole;
    case 2:
        return CurveRateRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case SampleRateRole:
        return aggregate()->sampleRate;
    case ControlRateRole:
        return aggregate()->controlRate;
    case CurveRateRole:
        return aggregate()->curveRate;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case SampleRateRole: {
        Aggregate *aggregate = this->aggregate();
        int rate = qvariant_cast<int>(value);
        rate = qMax(44100, rate);
        if (aggregate->sampleRate == rate)
            return false;
        ScopedDataChange data_change(this, SampleRateRole);
        aggregate->sampleRate = rate;
        return true;
    }
    case ControlRateRole: {
        Aggregate *aggregate = this->aggregate();
        int rate = qvariant_cast<int>(value);
        rate = qMax(1, rate);
        if (aggregate->controlRate == rate)
            return false;
        ScopedDataChange data_change(this, ControlRateRole);
        aggregate->controlRate = rate;
        return true;
    }
    case CurveRateRole: {
        Aggregate *aggregate = this->aggregate();
        int rate = qvariant_cast<int>(value);
        rate = qMax(1, rate);
        if (aggregate->curveRate == rate)
            return false;
        ScopedDataChange data_change(this, CurveRateRole);
        aggregate->curveRate = rate;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
