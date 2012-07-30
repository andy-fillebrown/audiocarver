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

#include "ac_core_scoreobject.h"

#include <mi_idatabase.h>
#include <mi_iclassfactory.h>

#include <mi_core_scopeddatachange.h>

using namespace Mi::Core;

namespace Ac {
namespace Core {

IAggregate *ScoreObject::initialize()
{
    IClassFactory *factory = query<IClassFactory>(IDatabase::instance());
    IModelItem *this_item = query<IModelItem>(this);
    _pitchCurve = factory->createAggregate(Ac::PitchCurveItem, this_item);
    _controlCurves = factory->createAggregate(Ac::ControlCurveListItem, this_item);
    return DatabaseObject::initialize();
}

ScoreObject::~ScoreObject()
{
    delete _controlCurves;
    delete _pitchCurve;
}

bool ScoreObject::setVolume(qreal volume)
{
    volume = qBound(qreal(0.0f), volume, qreal(1.0f));
    if (_volume == volume)
        return false;
    ScopedDataChange data_change(this, VolumeRole);
    _volume = volume;
    return true;
}

IUnknown *ScoreObject::ModelData::initialize()
{
    return DatabaseObject::ModelData::initialize();
}

IUnknown *ScoreObject::ModelItem::initialize()
{
    return DatabaseObject::ModelItem::initialize();
}

} // namespace Core
} // namespace Ac
