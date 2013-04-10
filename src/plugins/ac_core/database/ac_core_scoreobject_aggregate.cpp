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

#include "ac_core_scoreobject_aggregate.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace ScoreObject {

Aggregate::Aggregate(IAggregate *aggregate)
    :   Object::Aggregate(aggregate)
    ,   pitchCurve(0)
    ,   controlCurve(0)
    ,   volume(DEFAULT_SCOREOBJECT_VOLUME)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    pitchCurve = factory->create(PitchCurveItem, this);
    controlCurve = factory->create(ControlCurveItem, this);
}

Aggregate::~Aggregate()
{
    qDelete(controlCurve);
    qDelete(pitchCurve);
}

}
