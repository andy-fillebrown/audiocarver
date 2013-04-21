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

#include "ac_core_score_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include "ac_core_score_aggregate.h"
#include <mi_core_scopeddatachange.h>

using namespace Ac;

namespace Score {

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

int ModelItem::itemType() const
{
    return ScoreItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return ScoreItem == itemType;
}

int ModelItem::itemCount() const
{
    return Aggregate::TotalItemCount;
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(aggregate()->tracks) == item)
        return Aggregate::ItemCountOffset;
    if (query<IModelItem>(aggregate()->gridSettings) == item)
        return Aggregate::ItemCountOffset + 1;
    if (query<IModelItem>(aggregate()->projectSettings) == item)
        return Aggregate::ItemCountOffset + 2;
    if (query<IModelItem>(aggregate()->viewSettings) == item)
        return Aggregate::ItemCountOffset + 3;
    return Object::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    switch (i - Aggregate::ItemCountOffset) {
    case 0:
        return query<IModelItem>(aggregate()->tracks);
    case 1:
        return query<IModelItem>(aggregate()->gridSettings);
    case 2:
        return query<IModelItem>(aggregate()->projectSettings);
    case 3:
        return query<IModelItem>(aggregate()->viewSettings);
    default:
        return Object::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case TrackListItem:
        return query<IModelItem>(aggregate()->tracks);
    case GridSettingsItem:
        return query<IModelItem>(aggregate()->gridSettings);
    case ProjectSettingsItem:
        return query<IModelItem>(aggregate()->projectSettings);
    case ViewSettingsItem:
        return query<IModelItem>(aggregate()->viewSettings);
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
        return LengthRole;
    case 1:
        return StartTimeRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case LengthRole:
        return aggregate()->length;
    case StartTimeRole:
        return aggregate()->startTime;
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case LengthRole: {
        qreal length = qvariant_cast<qreal>(value);
        length = qMax(qreal(1.0f), length);
        if (aggregate()->length == length)
            return false;
        ScopedDataChange data_change(this, LengthRole);
        aggregate()->length = length;
        return true;
    }
    case StartTimeRole: {
        qreal startTime = qvariant_cast<qreal>(value);
        startTime = qBound(qreal(0.0f), startTime, aggregate()->length);
        if (aggregate()->startTime == startTime)
            return false;
        ScopedDataChange data_change(this, StartTimeRole);
        aggregate()->startTime = startTime;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
