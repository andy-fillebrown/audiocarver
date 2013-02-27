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

#include "ac_core_viewsettings_modeldata.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>
#include <idatabase.h>
#include <imodelitem.h>
#include <isession.h>

using namespace Ac;

namespace ViewSettings {

ModelData::ModelData(IAggregate *aggregate)
    :   Object::ModelData(aggregate)
    ,   _timePosition(DEFAULT_VIEWSETTINGS_TIMEPOSITION)
    ,   _pitchPosition(DEFAULT_VIEWSETTINGS_PITCHPOSITION)
    ,   _controlPosition(DEFAULT_VIEWSETTINGS_CONTROLPOSITION)
    ,   _timeScale(VIEWSCALE_MIN)
    ,   _pitchScale(VIEWSCALE_MIN)
    ,   _controlScale(VIEWSCALE_MIN)
{}

bool ModelData::setTimePosition(qreal position)
{
    IModelData *score_data = QUERY(IModelData, IDatabase::instance()->rootItem());
    position = qBound(qreal(0.0f), position, score_data->get<qreal>(LengthRole));
    if (_timePosition == position)
        return false;
    ScopedDataChange data_change(this, TimePositionRole);
    _timePosition = position;
    return true;
}

bool ModelData::setPitchPosition(qreal position)
{
    position = qBound(qreal(0.0f), position, qreal(127.0f));
    if (_pitchPosition == position)
        return false;
    ScopedDataChange data_change(this, PitchPositionRole);
    _pitchPosition = position;
    return true;
}

bool ModelData::setControlPosition(qreal position)
{
    position = qBound(qreal(0.0f), position, qreal(1.0f));
    if (_controlPosition == position)
        return false;
    ScopedDataChange data_change(this, ControlPositionRole);
    _controlPosition = position;
    return true;
}

bool ModelData::setTimeScale(qreal scale)
{
    scale = qBound(VIEWSCALE_MIN, scale, VIEWSCALE_MAX);
    if (_timeScale == scale)
        return false;
    ScopedDataChange data_change(this, TimeScaleRole);
    _timeScale = scale;
    return true;
}

bool ModelData::setPitchScale(qreal scale)
{
    scale = qBound(VIEWSCALE_MIN, scale, VIEWSCALE_MAX);
    if (_pitchScale == scale)
        return false;
    ScopedDataChange data_change(this, PitchScaleRole);
    _pitchScale = scale;
    return true;
}

bool ModelData::setControlScale(qreal scale)
{
    scale = qBound(VIEWSCALE_MIN, scale, VIEWSCALE_MAX);
    if (_controlScale == scale)
        return false;
    ScopedDataChange data_change(this, ControlScaleRole);
    _controlScale = scale;
    return true;
}

int ModelData::roleAt(int i) const
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
        return Object::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
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
        return Object::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case TimePositionRole:
        return setTimePosition(qvariant_cast<qreal>(value));
    case PitchPositionRole:
        return setPitchPosition(qvariant_cast<qreal>(value));
    case ControlPositionRole:
        return setControlPosition(qvariant_cast<qreal>(value));
    case TimeScaleRole:
        return setTimeScale(qvariant_cast<qreal>(value));
    case PitchScaleRole:
        return setPitchScale(qvariant_cast<qreal>(value));
    case ControlScaleRole:
        return setControlScale(qvariant_cast<qreal>(value));
    default:
        return Object::ModelData::setValue(value, role);
    }
}

}
