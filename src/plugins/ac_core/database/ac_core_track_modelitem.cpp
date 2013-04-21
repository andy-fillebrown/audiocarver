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

#include "ac_core_track_modelitem.h"
#include "ac_core_namespace.h"
#include "ac_core_track_aggregate.h"
#include <mi_core_scopeddatachange.h>
#include <mi_core_utilities.h>

using namespace Ac;
using namespace Mi;

namespace Track {

ModelItem::ModelItem(IAggregate *aggregate)
    :   Object::ModelItem(aggregate)
{}

Aggregate *ModelItem::aggregate() const
{
    return static_cast<Aggregate*>(Base::ModelItem::aggregate());
}

int ModelItem::itemType() const
{
    return TrackItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    return TrackItem == itemType;
}

int ModelItem::itemCount() const
{
    return Aggregate::TotalItemCount;
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(aggregate()->notes) == item)
        return Aggregate::ItemCountOffset;
    return Object::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    Q_ASSERT(0 <= (Aggregate::TotalItemCount - i));
    switch (i - Aggregate::ItemCountOffset) {
    case 0:
        return query<IModelItem>(aggregate()->notes);
    default:
        return Object::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case NoteListItem:
        return query<IModelItem>(aggregate()->notes);
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
        return ColorRole;
    case 1:
        return InstrumentRole;
    case 2:
        return VisibilityRole;
    case 3:
        return RecordingRole;
    default:
        return Object::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case ColorRole:
        return colorFromInt(aggregate()->color);
    case InstrumentRole:
        return aggregate()->instrument;
    case VisibilityRole:
        return bool(aggregate()->visible);
    case RecordingRole:
        return bool(aggregate()->recording);
    default:
        return Object::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case ColorRole: {
        Aggregate *aggregate = this->aggregate();
        const int color = intFromColor(value);
        if (aggregate->color == color)
            return false;
        ScopedDataChange data_change(this, ColorRole);
        aggregate->color = color;
        return true;
    }
    case InstrumentRole: {
        Aggregate *aggregate = this->aggregate();
        const QString instrument = qvariant_cast<QString>(value);
        if (aggregate->instrument == instrument)
            return false;
        ScopedDataChange data_change(this, InstrumentRole);
        aggregate->instrument = instrument;
        return true;
    }
    case VisibilityRole: {
        Aggregate *aggregate = this->aggregate();
        const bool visible = qvariant_cast<bool>(value);
        if (aggregate->visible == visible)
            return false;
        ScopedDataChange data_change(this, VisibilityRole);
        aggregate->visible = visible;
        return true;
    }
    case RecordingRole: {
        const bool recording = qvariant_cast<bool>(value);
        Aggregate *aggregate = this->aggregate();
        if (aggregate->recording == recording)
            return false;
        ScopedDataChange data_change(this, RecordingRole);
        aggregate->recording = recording;
        return true;
    }
    default:
        return Object::ModelItem::setValue(role, value);
    }
}

}
