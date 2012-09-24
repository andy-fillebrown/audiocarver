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

#include "ac_core_scoreobject_modeldata.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace ScoreObject {

ModelData::ModelData(IAggregate *aggregate)
    :   Object::ModelData(aggregate)
    ,   _volume(DEFAULT_SCOREOBJECT_VOLUME)
{}

IUnknown *ModelData::initialize()
{
    return Object::ModelData::initialize();
}

bool ModelData::setVolume(qreal volume)
{
    volume = qBound(qreal(0.0f), volume, qreal(1.0f));
    if (_volume == volume)
        return false;
    ScopedDataChange data_change(this, VolumeRole);
    _volume = volume;
    return true;
}

int ModelData::roleCount() const
{
    return TotalRoleCount;
}

int ModelData::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return VolumeRole;
    default:
        return Object::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case VolumeRole:
        return volume();
    default:
        return Object::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case VolumeRole:
        return setVolume(qvariant_cast<qreal>(value));
    default:
        return Object::ModelData::setValue(value, role);
    }
}

}
