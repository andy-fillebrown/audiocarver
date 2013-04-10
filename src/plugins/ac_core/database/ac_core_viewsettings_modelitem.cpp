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

#include "ac_core_viewsettings_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include "ac_core_viewsettings_aggregate.h"
#include <mi_core_scopeddatachange.h>
#include <idatabase.h>

using namespace Ac;

namespace ViewSettings {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

int ModelItem::itemType() const
{
    return ViewSettingsItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ViewSettingsItem == itemType;
}

int ModelItem::roleCount() const
{
    return Aggregate::TotalRoleCount;
}

int ModelItem::roleAt(int i) const
{
    switch (i - Aggregate::RoleCountOffset) {
    case 0:
        return TimePositionRole;
    case 1:
        return PitchPositionRole;
    case 2:
        return ControlPositionRole;
    case 3:
        return TimeScaleRole;
    case 4:
        return PitchScaleRole;
    case 5:
        return ControlScaleRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case TimePositionRole:
        return aggregate()->timePosition;
    case PitchPositionRole:
        return aggregate()->pitchPosition;
    case ControlPositionRole:
        return aggregate()->controlPosition;
    case TimeScaleRole:
        return aggregate()->timeScale;
    case PitchScaleRole:
        return aggregate()->pitchScale;
    case ControlScaleRole:
        return aggregate()->controlScale;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case TimePositionRole: {
        Aggregate *aggregate = this->aggregate();
        qreal position = qBound(qreal(0.0f), qvariant_cast<qreal>(value), get<qreal>(IDatabase::instance()->rootItem(), LengthRole));
        if (aggregate->timePosition == position)
            return false;
        ScopedDataChange data_change(this, TimePositionRole);
        aggregate->timePosition = position;
        return true;
    }
    case PitchPositionRole: {
        Aggregate *aggregate = this->aggregate();
        qreal position = qBound(qreal(0.0f), qvariant_cast<qreal>(value), qreal(127.0f));
        if (aggregate->pitchPosition == position)
            return false;
        ScopedDataChange data_change(this, PitchPositionRole);
        aggregate->pitchPosition = position;
        return true;
    }
    case ControlPositionRole: {
        Aggregate *aggregate = this->aggregate();
        qreal position = qBound(qreal(0.0f), qvariant_cast<qreal>(value), qreal(1.0f));
        if (aggregate->controlPosition == position)
            return false;
        ScopedDataChange data_change(this, ControlPositionRole);
        aggregate->controlPosition = position;
        return true;
    }
    case TimeScaleRole: {
        Aggregate *aggregate = this->aggregate();
        qreal scale = qBound(qreal(VIEWSCALE_MIN), qvariant_cast<qreal>(value), qreal(VIEWSCALE_MAX));
        if (aggregate->timeScale == scale)
            return false;
        ScopedDataChange data_change(this, TimeScaleRole);
        aggregate->timeScale = scale;
        return true;
    }
    case PitchScaleRole: {
        Aggregate *aggregate = this->aggregate();
        qreal scale = qBound(qreal(VIEWSCALE_MIN), qvariant_cast<qreal>(value), qreal(VIEWSCALE_MAX));
        if (aggregate->pitchScale == scale)
            return false;
        ScopedDataChange data_change(this, PitchScaleRole);
        aggregate->pitchScale = scale;
        return true;
    }
    case ControlScaleRole: {
        Aggregate *aggregate = this->aggregate();
        qreal scale = qBound(qreal(VIEWSCALE_MIN), qvariant_cast<qreal>(value), qreal(VIEWSCALE_MAX));
        if (aggregate->controlScale == scale)
            return false;
        ScopedDataChange data_change(this, ControlScaleRole);
        aggregate->controlScale = scale;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
