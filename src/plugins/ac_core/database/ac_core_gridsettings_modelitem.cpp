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

#include "ac_core_gridsettings_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_gridsettings_aggregate.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace GridSettings {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

int ModelItem::itemType() const
{
    return GridSettingsItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return GridSettingsItem == itemType;
}

int ModelItem::itemCount() const
{
    return Aggregate::TotalItemCount;
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(aggregate()->timeGridLines) == item)
        return Aggregate::ItemCountOffset;
    if (query<ModelItem>(aggregate()->pitchGridLines) == item)
        return Aggregate::ItemCountOffset + 1;
    if (query<IModelItem>(aggregate()->controlGridLines) == item)
        return Aggregate::ItemCountOffset + 2;
    return Object::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    switch (i - Aggregate::ItemCountOffset) {
    case 0:
        return query<IModelItem>(aggregate()->timeGridLines);
    case 1:
        return query<ModelItem>(aggregate()->pitchGridLines);
    case 2:
        return query<IModelItem>(aggregate()->controlGridLines);
    default:
        return Object::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case TimeGridLineListItem:
        return query<IModelItem>(aggregate()->timeGridLines);
    case PitchGridLineListItem:
        return query<ModelItem>(aggregate()->pitchGridLines);
    case ControlGridLineListItem:
        return query<IModelItem>(aggregate()->controlGridLines);
    default:
        return Object::ModelItem::findItem(itemType);
    }
}

int ModelItem::roleCount() const
{
    return Aggregate::TotalRoleCount;
}

int ModelItem::roleAt(int i) const
{
    switch (i - Aggregate::RoleCountOffset) {
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
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case SnapEnabledRole:
        return bool(aggregate()->snapEnabled);
    case GridSnapEnabledRole:
        return bool(aggregate()->gridSnapEnabled);
    case TimeSnapRole:
        return aggregate()->timeSnap;
    case PitchSnapRole:
        return aggregate()->pitchSnap;
    case ControlSnapRole:
        return aggregate()->controlSnap;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case SnapEnabledRole: {
        Aggregate *aggregate = this->aggregate();
        const bool enabled = qvariant_cast<bool>(value);
        if (aggregate->snapEnabled == enabled)
            return false;
        ScopedDataChange data_change(this, SnapEnabledRole);
        aggregate->snapEnabled = enabled;
        return true;
    }
    case GridSnapEnabledRole: {
        Aggregate *aggregate = this->aggregate();
        const bool enabled = qvariant_cast<bool>(value);
        if (aggregate->gridSnapEnabled == enabled)
            return false;
        ScopedDataChange data_change(this, GridSnapEnabledRole);
        aggregate->gridSnapEnabled = enabled;
        return true;
    }
    case TimeSnapRole: {
        Aggregate *aggregate = this->aggregate();
        const qreal snap = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (aggregate->timeSnap == snap)
            return false;
        ScopedDataChange data_change(this, TimeSnapRole);
        aggregate->timeSnap = snap;
        return true;
    }
    case PitchSnapRole: {
        Aggregate *aggregate = this->aggregate();
        const qreal snap = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (aggregate->pitchSnap == snap)
            return false;
        ScopedDataChange data_change(this, PitchSnapRole);
        aggregate->pitchSnap = snap;
        return true;
    }
    case ControlSnapRole: {
        Aggregate *aggregate = this->aggregate();
        const qreal snap = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (aggregate->controlSnap == snap)
            return false;
        ScopedDataChange data_change(this, ControlSnapRole);
        aggregate->controlSnap = snap;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
