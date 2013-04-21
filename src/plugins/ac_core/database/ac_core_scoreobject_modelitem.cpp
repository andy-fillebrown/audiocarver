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
#include "ac_core_namespace.h"
#include "ac_core_scoreobject_aggregate.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace ScoreObject {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ScoreObjectItem == itemType;
}

int ModelItem::itemCount() const
{
    return Aggregate::TotalItemCount;
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(aggregate()->pitchCurve) == item)
        return Aggregate::ItemCountOffset;
    if (query<IModelItem>(aggregate()->controlCurve) == item)
        return Aggregate::ItemCountOffset + 1;
    return Object::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    switch (i - Aggregate::ItemCountOffset) {
    case 0:
        return query<IModelItem>(aggregate()->pitchCurve);
    case 1:
        return query<IModelItem>(aggregate()->controlCurve);
    default:
        return Object::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case ControlCurveListItem:
        return query<IModelItem>(aggregate()->controlCurve);
    case PitchCurveItem:
        return query<IModelItem>(aggregate()->pitchCurve);
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
        return VolumeRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case VolumeRole:
        return aggregate()->volume;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case VolumeRole: {
        qreal volume = qvariant_cast<qreal>(value);
        volume = qBound(qreal(0.0f), volume, qreal(1.0f));
        if (aggregate()->volume == volume)
            return false;
        ScopedDataChange data_change(this, VolumeRole);
        aggregate()->volume = volume;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
