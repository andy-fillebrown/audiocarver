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

#include "ac_core_gridsettings_aggregate.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <mi_core_scopeddatachange.h>
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace GridSettings {

Aggregate::Aggregate(IAggregate *parent)
    :   Object::Aggregate(parent)
    ,   timeGridLines(0)
    ,   pitchGridLines(0)
    ,   controlGridLines(0)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    timeGridLines = factory->create(TimeGridLineListItem, this);
    pitchGridLines = factory->create(PitchGridLineListItem, this);
    controlGridLines = factory->create(ControlGridLineListItem, this);
    reset();
}

Aggregate::~Aggregate()
{
    qDelete(controlGridLines);
    qDelete(pitchGridLines);
    qDelete(timeGridLines);
}

void Aggregate::reset()
{
    snapEnabled = DEFAULT_GRIDSETTINGS_SNAPENABLED;
    gridSnapEnabled = DEFAULT_GRIDSETTINGS_GRIDSNAPENABLED;
    timeSnap = DEFAULT_GRIDSETTINGS_TIMESNAP;
    pitchSnap = DEFAULT_GRIDSETTINGS_PITCHSNAP;
    controlSnap = DEFAULT_GRIDSETTINGS_CONTROLSNAP;
}

}
