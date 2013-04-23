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

#include "ac_core_scoreobject_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace ScoreObject {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Object::ModelItem(aggregate)
{
    reset();
}

void ModelItem::reset()
{
    _volume = DEFAULT_SCOREOBJECT_VOLUME;
    Object::ModelItem::reset();
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ScoreObjectItem == itemType;
}

int ModelItem::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return VolumeRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case VolumeRole:
        return _volume;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case VolumeRole: {
        qreal volume = qBound(qreal(0.0f), qvariant_cast<qreal>(value), qreal(1.0f));
        if (_volume == volume)
            return false;
        ScopedDataChange data_change(this, VolumeRole);
        _volume = volume;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
