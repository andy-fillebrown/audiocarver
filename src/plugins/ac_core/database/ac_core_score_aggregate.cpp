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

#include "ac_core_score_aggregate.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <idatabaseobjectfactory.h>

using namespace Ac;

namespace Score {

Aggregate::Aggregate(IAggregate *aggregate)
    :   Object::Aggregate(aggregate)
    ,   tracks(0)
    ,   gridSettings(0)
    ,   projectSettings(0)
    ,   viewSettings(0)
{
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    tracks = factory->create(TrackListItem, this);
    gridSettings = factory->create(GridSettingsItem, this);
    projectSettings = factory->create(ProjectSettingsItem, this);
    viewSettings = factory->create(ViewSettingsItem, this);
    reset();
}

Aggregate::~Aggregate()
{
    qDelete(viewSettings);
    qDelete(projectSettings);
    qDelete(gridSettings);
    qDelete(tracks);
}

void Aggregate::reset()
{
    length = DEFAULT_SCORE_LENGTH;
    startTime = DEFAULT_SCORE_STARTTIME;
}

}
