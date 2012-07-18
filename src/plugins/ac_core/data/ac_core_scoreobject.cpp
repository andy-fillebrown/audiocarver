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
#include <mi_idataobjectfactory.h>

#include <mi_core_scopeddatachange.h>

namespace Ac {
namespace Core {

using namespace Mi::Core;

IAggregator *ScoreObject::init()
{
    IDataObjectFactory *factory = query<IDataObjectFactory>(IDatabase::instance());
    _pitchCurve = factory->create(Ac::PitchCurveItem);
    _controlCurves = factory->create(Ac::ControlCurveListItem);
    return DataObject::init();
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
    ScopedDataChange data_change(this, Ac::VolumeRole);
    _volume = volume;
    return true;
}

IAggregate *ScoreObject::ModelData::init()
{
    return DataObject::ModelData::init();
}

IAggregate *ScoreObject::ModelItem::init()
{
    return DataObject::ModelItem::init();
}

} // namespace Core
} // namespace Ac
