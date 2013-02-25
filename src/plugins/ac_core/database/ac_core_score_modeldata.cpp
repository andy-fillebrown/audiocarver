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

#include "ac_core_score_modeldata.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace Score {

ModelData::ModelData(IAggregate *aggregate)
    :   ScoreObject::ModelData(aggregate)
    ,   _length(DEFAULT_SCORE_LENGTH)
    ,   _startTime(DEFAULT_SCORE_STARTTIME)
{}

bool ModelData::setLength(qreal length)
{
    length = qMax(qreal(1.0f), length);
    if (_length == length)
        return false;
    ScopedDataChange data_change(this, LengthRole);
    _length = length;
    return true;
}

bool ModelData::setStartTime(qreal time)
{
    time = qBound(qreal(0.0f), time, _length);
    if (_startTime == time)
        return false;
    ScopedDataChange data_change(this, StartTimeRole);
    _startTime = time;
    return true;
}

int ModelData::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return LengthRole;
    case 1:
        return StartTimeRole;
    default:
        return ScoreObject::ModelData::roleAt(i);
    }
}

QVariant ModelData::getValue(int role) const
{
    switch (role) {
    case LengthRole:
        return _length;
    case StartTimeRole:
        return _startTime;
    default:
        return ScoreObject::ModelData::getValue(role);
    }
}

bool ModelData::setValue(const QVariant &value, int role)
{
    switch (role) {
    case LengthRole:
        return setLength(qvariant_cast<qreal>(value));
    case StartTimeRole:
        return setStartTime(qvariant_cast<qreal>(value));
    default:
        return ScoreObject::ModelData::setValue(value, role);
    }
}

}
