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

#include "ac_database_scoreobject.h"

#include <mi_idatabaseobjectfactory.h>
#include <mi_scopeddatachange.h>

namespace Database {

IAggregator *ScoreObject::init()
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    _pitchCurve = factory->createObject(Ac::PitchCurveItem);
    _controlCurves = factory->createObjectList(Ac::ControlCurveItem);
    return Object::init();
}

ScoreObject::~ScoreObject()
{
    delete _controlCurves;
    delete _pitchCurve;
}

IAggregate *ScoreObject::ModelData::init()
{
    return Object::ModelData::init();
}

IAggregate *ScoreObject::ModelItem::init()
{
    return Object::ModelItem::init();
}

bool ScoreObject::setVolume(qreal volume)
{
    volume = qBound(qreal(0.0f), volume, qreal(1.0f));
    if (_volume == volume)
        return false;
    ScopedDataChange data_change(this, Ac::VolumeRole);
    _volume = volume;
    updatePoints();
    return true;
}

} // namespace Database
