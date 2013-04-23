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
#include <mi_core_scopeddatachange.h>
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace Score {

ModelItem::ModelItem(IAggregate *aggregate)
    :   ScoreObject::ModelItem(aggregate)
    ,   _tracks(0)
    ,   _gridSettings(0)
    ,   _projectSettings(0)
    ,   _viewSettings(0)
{}

void ModelItem::initialize()
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _tracks = factory->create(TrackListItem, this);
    _gridSettings = factory->create(GridSettingsItem, this);
    _projectSettings = factory->create(ProjectSettingsItem, this);
    _viewSettings = factory->create(ViewSettingsItem, this);
    reset();
    ScoreObject::ModelItem::initialize();
}

ModelItem::~ModelItem()
{
    qDelete(_viewSettings);
    qDelete(_projectSettings);
    qDelete(_gridSettings);
    qDelete(_tracks);
}

void ModelItem::reset()
{
    _length = DEFAULT_SCORE_LENGTH;
    _startTime = DEFAULT_SCORE_STARTTIME;
    ScoreObject::ModelItem::reset();
}

int ModelItem::itemType() const
{
    return ScoreItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (ScoreItem == itemType)
        return true;
    return ScoreObject::ModelItem::isTypeOfItem(itemType);
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(_tracks) == item)
        return ItemCountOffset;
    if (query<IModelItem>(_gridSettings) == item)
        return ItemCountOffset + 1;
    if (query<IModelItem>(_projectSettings) == item)
        return ItemCountOffset + 2;
    if (query<IModelItem>(_viewSettings) == item)
        return ItemCountOffset + 3;
    return ScoreObject::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(_tracks);
    case 1:
        return query<IModelItem>(_gridSettings);
    case 2:
        return query<IModelItem>(_projectSettings);
    case 3:
        return query<IModelItem>(_viewSettings);
    default:
        return ScoreObject::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case TrackListItem:
        return query<IModelItem>(_tracks);
    case GridSettingsItem:
        return query<IModelItem>(_gridSettings);
    case ProjectSettingsItem:
        return query<IModelItem>(_projectSettings);
    case ViewSettingsItem:
        return query<IModelItem>(_viewSettings);
    default:
        return ScoreObject::ModelItem::findItem(itemType);
    }
}

int ModelItem::roleAt(int i) const
{
    switch (i - RoleCountOffset) {
    case 0:
        return LengthRole;
    case 1:
        return StartTimeRole;
    default:
        return ScoreObject::ModelItem::roleAt(i);
    }
}

QVariant ModelItem::getValue(int role) const
{
    switch (role) {
    case LengthRole:
        return _length;
    case StartTimeRole:
        return _startTime;
    default:
        return ScoreObject::ModelItem::getValue(role);
    }
}

bool ModelItem::setValue(int role, const QVariant &value)
{
    switch (role) {
    case LengthRole: {
        qreal length = qMax(qreal(1.0f), qvariant_cast<qreal>(value));
        if (_length == length)
            return false;
        ScopedDataChange data_change(this, LengthRole);
        _length = length;
        setValue(StartTimeRole, _startTime);
        return true;
    }
    case StartTimeRole: {
        qreal startTime = qBound(qreal(0.0f), qvariant_cast<qreal>(value), _length);
        if (_startTime == startTime)
            return false;
        ScopedDataChange data_change(this, StartTimeRole);
        _startTime = startTime;
        return true;
    }
    default:
        return ScoreObject::ModelItem::setValue(role, value);
    }
}

}
