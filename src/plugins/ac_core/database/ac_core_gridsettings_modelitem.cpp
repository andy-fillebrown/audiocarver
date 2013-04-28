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
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace GridSettings {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Object::ModelItem(aggregate)
    ,   _timeGridLines(0)
    ,   _pitchGridLines(0)
    ,   _controlGridLines(0)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _timeGridLines = factory->create(TimeGridLineListItem, this);
    _pitchGridLines = factory->create(PitchGridLineListItem, this);
    _controlGridLines = factory->create(ControlGridLineListItem, this);
    reset();
}

ModelItem::~ModelItem()
{
    qDelete(_controlGridLines);
    qDelete(_pitchGridLines);
    qDelete(_timeGridLines);
}

void ModelItem::reset()
{
    _snapEnabled = DEFAULT_GRIDSETTINGS_SNAPENABLED;
    _gridSnapEnabled = DEFAULT_GRIDSETTINGS_GRIDSNAPENABLED;
    _timeSnap = DEFAULT_GRIDSETTINGS_TIMESNAP;
    _pitchSnap = DEFAULT_GRIDSETTINGS_PITCHSNAP;
    _controlSnap = DEFAULT_GRIDSETTINGS_CONTROLSNAP;
    Object::ModelItem::reset();
}

int ModelItem::itemType() const
{
    return GridSettingsItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return GridSettingsItem == itemType;
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(_timeGridLines) == item)
        return ItemCountOffset;
    if (query<ModelItem>(_pitchGridLines) == item)
        return ItemCountOffset + 1;
    if (query<IModelItem>(_controlGridLines) == item)
        return ItemCountOffset + 2;
    return Object::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(_timeGridLines);
    case 1:
        return query<ModelItem>(_pitchGridLines);
    case 2:
        return query<IModelItem>(_controlGridLines);
    default:
        return Object::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case TimeGridLineListItem:
        return query<IModelItem>(_timeGridLines);
    case PitchGridLineListItem:
        return query<ModelItem>(_pitchGridLines);
    case ControlGridLineListItem:
        return query<IModelItem>(_controlGridLines);
    default:
        return Object::ModelItem::findItem(itemType);
    }
}


int ModelItem::roleAt(int i) const
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
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case SnapEnabledRole:
        return bool(_snapEnabled);
    case GridSnapEnabledRole:
        return bool(_gridSnapEnabled);
    case TimeSnapRole:
        return _timeSnap;
    case PitchSnapRole:
        return _pitchSnap;
    case ControlSnapRole:
        return _controlSnap;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case SnapEnabledRole: {
        const bool enabled = qvariant_cast<bool>(value);
        if (_snapEnabled == enabled)
            return false;
        ScopedDataChange data_change(this, SnapEnabledRole);
        _snapEnabled = enabled;
        return true;
    }
    case GridSnapEnabledRole: {
        const bool enabled = qvariant_cast<bool>(value);
        if (_gridSnapEnabled == enabled)
            return false;
        ScopedDataChange data_change(this, GridSnapEnabledRole);
        _gridSnapEnabled = enabled;
        return true;
    }
    case TimeSnapRole: {
        const qreal snap = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (_timeSnap == snap)
            return false;
        ScopedDataChange data_change(this, TimeSnapRole);
        _timeSnap = snap;
        return true;
    }
    case PitchSnapRole: {
        const qreal snap = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (_pitchSnap == snap)
            return false;
        ScopedDataChange data_change(this, PitchSnapRole);
        _pitchSnap = snap;
        return true;
    }
    case ControlSnapRole: {
        const qreal snap = qMax(qreal(0.0f), qvariant_cast<qreal>(value));
        if (_controlSnap == snap)
            return false;
        ScopedDataChange data_change(this, ControlSnapRole);
        _controlSnap = snap;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
