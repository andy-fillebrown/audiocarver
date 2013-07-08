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
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>
#include <mi_core_utilities.h>
#include <idatabaseobjectfactory.h>

using namespace Ac;
using namespace Mi;

namespace Track {

ModelItem::ModelItem(IAggregate *aggregate)
    :   ScoreObject::ModelItem(aggregate)
    ,   _notes(0)
    ,   _color(DEFAULT_TRACK_COLOR)
    ,   _visible(true)
{
    _notes = IDatabaseObjectFactory::instance()->create(NoteListItem, this);
}

ModelItem::~ModelItem()
{
    qDelete(_notes);
}

int ModelItem::itemType() const
{
    return TrackItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (TrackItem == itemType)
        return true;
    return ScoreObject::ModelItem::isTypeOfItem(itemType);
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(_notes) == item)
        return ItemCountOffset;
    return ScoreObject::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    Q_ASSERT(0 <= (TotalItemCount - i));
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(_notes);
    default:
        return ScoreObject::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case NoteListItem:
        return query<IModelItem>(_notes);
    default:
        return ScoreObject::ModelItem::findItem(itemType);
    }
}

int ModelItem::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return ColorRole;
    case 1:
        return InstrumentRole;
    case 2:
        return VisibilityRole;
    default:
        return ScoreObject::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case ColorRole:
        return colorFromInt(_color);
    case InstrumentRole:
        return _instrument;
    case VisibilityRole:
        return bool(_visible);
    default:
        return ScoreObject::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case ColorRole: {
        const int color = intFromColor(value);
        if (_color == color)
            return false;
        ScopedDataChange data_change(this, ColorRole);
        _color = color;
        return true;
    }
    case InstrumentRole: {
        const QString instrument = qvariant_cast<QString>(value);
        if (_instrument == instrument)
            return false;
        ScopedDataChange data_change(this, InstrumentRole);
        _instrument = instrument;
        return true;
    }
    case VisibilityRole: {
        const bool visible = qvariant_cast<bool>(value);
        if (_visible == visible)
            return false;
        ScopedDataChange data_change(this, VisibilityRole);
        _visible = visible;
        return true;
    }
    default:
        return ScoreObject::ModelItem::setValue(role, value);
    }
}

}
