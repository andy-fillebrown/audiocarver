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

#include "ac_core_database_scoreobject_aggregate.h"

#include <mi_idatabase.h>
#include <mi_iclassfactory.h>
#include <mi_imodelitem.h>

#include "ac_core_constants.h"
#include "ac_core_namespace.h"

#include <mi_core_scopeddatachange.h>

using namespace Mi::Core;

namespace Ac {
namespace Core {
namespace Database {
namespace ScoreObject {

Aggregate::Aggregate()
    :   _volume(DEFAULT_SCOREOBJECT_VOLUME)
    ,   _pitchCurve(0)
    ,   _controlCurves(0)
{}

Aggregate::~Aggregate()
{
    delete _controlCurves;
    delete _pitchCurve;
}

IAggregate *Aggregate::initialize()
{
    IClassFactory *factory = IClassFactory::instance();
    IModelItem *this_item = query<IModelItem>(this);
    _pitchCurve = factory->createAggregate(PitchCurveItem, this_item);
    _controlCurves = factory->createAggregate(ControlCurveListItem, this_item);
    return Aggregate_BaseClass::initialize();
}

bool Aggregate::setVolume(qreal volume)
{
    volume = qBound(qreal(0.0f), volume, qreal(1.0f));
    if (_volume == volume)
        return false;
    ScopedDataChange data_change(this, VolumeRole);
    _volume = volume;
    return true;
}

void Aggregate::clear()
{
    _controlCurves->clear();
    _pitchCurve->clear();
    setVolume(DEFAULT_SCOREOBJECT_VOLUME);
    Aggregate_BaseClass::clear();
}

}
}
}
}
