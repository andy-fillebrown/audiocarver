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

#include "ac_core_note_modelitem.h"
#include "ac_core_namespace.h"
#include <iaggregate.h>
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace Note {

ModelItem::ModelItem(IAggregate *aggregate)
    :   ScoreObject::ModelItem(aggregate)
    ,   _pitchCurve(0)
    ,   _controlCurves(0)
{}

void ModelItem::initialize()
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _pitchCurve = factory->create(PitchCurveItem, this);
    _controlCurves = factory->create(ControlCurveListItem, this);
    ScoreObject::ModelItem::initialize();
}

ModelItem::~ModelItem()
{
    qDelete(_controlCurves);
    qDelete(_pitchCurve);
}

int ModelItem::itemType() const
{
    return NoteItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (NoteItem == itemType)
        return true;
    return ScoreObject::ModelItem::isTypeOfItem(itemType);
}

int ModelItem::indexOfItem(const IModelItem *item) const
{
    if (query<IModelItem>(_pitchCurve) == item)
        return ItemCountOffset;
    if (query<IModelItem>(_controlCurves) == item)
        return ItemCountOffset + 1;
    return ScoreObject::ModelItem::indexOfItem(item);
}

IModelItem *ModelItem::itemAt(int i) const
{
    switch (i - ItemCountOffset) {
    case 0:
        return query<IModelItem>(_pitchCurve);
    case 1:
        return query<IModelItem>(_controlCurves);
    default:
        return Object::ModelItem::itemAt(i);
    }
}

IModelItem *ModelItem::findItem(int itemType) const
{
    switch (itemType) {
    case ControlCurveListItem:
        return query<IModelItem>(_controlCurves);
    case PitchCurveItem:
        return query<IModelItem>(_pitchCurve);
    default:
        return Object::ModelItem::findItem(itemType);
    }
}

}
