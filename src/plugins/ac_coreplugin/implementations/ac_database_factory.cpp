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

#include "ac_database_factory.h"

#include <ac_database_controlcurve.h>
#include <ac_database_gridline.h>
#include <ac_database_gridsettings.h>
#include <ac_database_note.h>
#include <ac_database_pitchcurve.h>
#include <ac_database_projectsettings.h>
#include <ac_database_score.h>
#include <ac_database_track.h>
#include <ac_database_viewsettings.h>

static IFactory *instance = 0;

namespace Database {

IFactory *Factory::instance()
{
    return ::instance;
}

Factory::Factory()
{
    if (::instance)
        delete ::instance;
    ::instance = this;
}

IAggregator *Factory::createItem(int itemType)
{
    switch (itemType) {
    case Ac::ControlCurveItem:
        return (new ControlCurve)->init();
    case Ac::ControlGridLineItem:
        return (new ControlGridLine)->init();
    case Ac::GridSettingsItem:
        return (new GridSettings)->init();
    case Ac::NoteItem:
        return (new Note)->init();
    case Ac::PitchCurveItem:
        return (new PitchCurve)->init();
    case Ac::PitchGridLineItem:
        return (new PitchGridLine)->init();
    case Ac::ScoreItem:
        return (new Score)->init();
    case Ac::TimeGridLineItem:
        return (new TimeGridLine)->init();
    case Ac::TrackItem:
        return (new Track)->init();
    case Ac::ViewSettingsItem:
        return (new ViewSettings)->init();
    default:
        return 0;
    }
}

IAggregator *Factory::createList(int itemType, int listType)
{
    switch (listType) {
    case Mi::ListItem:
        return (new ObjectList(itemType))->init();
    default:
        return 0;
    }
}

} // namespace Database
