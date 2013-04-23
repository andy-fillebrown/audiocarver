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
#include <mi_core_scopeddatachange.h>
#include <idatabase.h>

using namespace Ac;

namespace ViewSettings {

ModelItem::ModelItem(IAggregate *parent)
    :   Object::ModelItem(parent)
{
    reset();
}

void ModelItem::reset()
{
    _timePosition = DEFAULT_VIEWSETTINGS_TIMEPOSITION;
    _pitchPosition = DEFAULT_VIEWSETTINGS_PITCHPOSITION;
    _controlPosition = DEFAULT_VIEWSETTINGS_CONTROLPOSITION;
    _timeScale = VIEWSCALE_MIN;
    _pitchScale = VIEWSCALE_MIN;
    _controlScale = VIEWSCALE_MIN;
}

int ModelItem::itemType() const
{
    return ViewSettingsItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ViewSettingsItem == itemType;
}

int ModelItem::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
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
        return _timePosition;
    case PitchPositionRole:
        return _pitchPosition;
    case ControlPositionRole:
        return _controlPosition;
    case TimeScaleRole:
        return _timeScale;
    case PitchScaleRole:
        return _pitchScale;
    case ControlScaleRole:
        return _controlScale;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case TimePositionRole: {
        const qreal position = qBound(qreal(0.0f), qvariant_cast<qreal>(value), get<qreal>(IDatabase::instance()->rootItem(), LengthRole));
        if (_timePosition == position)
            return false;
        ScopedDataChange data_change(this, TimePositionRole);
        _timePosition = position;
        return true;
    }
    case PitchPositionRole: {
        const qreal position = qBound(qreal(0.0f), qvariant_cast<qreal>(value), qreal(127.0f));
        if (_pitchPosition == position)
            return false;
        ScopedDataChange data_change(this, PitchPositionRole);
        _pitchPosition = position;
        return true;
    }
    case ControlPositionRole: {
        const qreal position = qBound(qreal(0.0f), qvariant_cast<qreal>(value), qreal(1.0f));
        if (_controlPosition == position)
            return false;
        ScopedDataChange data_change(this, ControlPositionRole);
        _controlPosition = position;
        return true;
    }
    case TimeScaleRole: {
        qreal scale = qBound(qreal(VIEWSCALE_MIN), qvariant_cast<qreal>(value), qreal(VIEWSCALE_MAX));
        if (_timeScale == scale)
            return false;
        ScopedDataChange data_change(this, TimeScaleRole);
        _timeScale = scale;
        return true;
    }
    case PitchScaleRole: {
        qreal scale = qBound(qreal(VIEWSCALE_MIN), qvariant_cast<qreal>(value), qreal(VIEWSCALE_MAX));
        if (_pitchScale == scale)
            return false;
        ScopedDataChange data_change(this, PitchScaleRole);
        _pitchScale = scale;
        return true;
    }
    case ControlScaleRole: {
        qreal scale = qBound(qreal(VIEWSCALE_MIN), qvariant_cast<qreal>(value), qreal(VIEWSCALE_MAX));
        if (_controlScale == scale)
            return false;
        ScopedDataChange data_change(this, ControlScaleRole);
        _controlScale = scale;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
