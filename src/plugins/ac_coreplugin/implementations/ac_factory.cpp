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

#include "ac_factory.h"

#include <ac_database.h>
#include <ac_database_controlcurve.h>
#include <ac_database_gridline.h>
#include <ac_database_gridsettings.h>
#include <ac_database_note.h>
#include <ac_database_pitchcurve.h>
#include <ac_database_projectsettings.h>
#include <ac_database_score.h>
#include <ac_database_track.h>
#include <ac_database_viewsettings.h>

using namespace Ac;

namespace Database {

IAggregate *Factory::init()
{
    return this;
}

IAggregator *Factory::create(int itemType)
{
    switch (itemType) {
    case ControlCurveItem:
        return (new ControlCurve)->init();
    case ControlCurveListItem:
        return (new ObjectList(ControlCurveItem))->init();
    case ControlGridLineItem:
        return (new ControlGridLine)->init();
    case ControlGridLineListItem:
        return (new ObjectList(ControlGridLineItem))->init();
    case GridSettingsItem:
        return (new GridSettings)->init();
    case NoteItem:
        return (new Note)->init();
    case NoteListItem:
        return (new ObjectList(NoteItem))->init();
    case PitchCurveItem:
        return (new PitchCurve)->init();
    case PitchGridLineItem:
        return (new PitchGridLine)->init();
    case PitchGridLineListItem:
        return (new ObjectList(PitchGridLineItem))->init();
    case ScoreItem:
        return (new Score)->init();
    case TimeGridLineItem:
        return (new TimeGridLine)->init();
    case TimeGridLineListItem:
        return (new ObjectList(TimeGridLineItem))->init();
    case TrackItem:
        return (new Track)->init();
    case TrackListItem:
        return (new ObjectList(TrackItem))->init();
    case ViewSettingsItem:
        return (new ViewSettings)->init();
    default:
        return 0;
    }
}

IAggregator *Factory::aggregator() const
{
    return _aggregator;
}

} // namespace Database
