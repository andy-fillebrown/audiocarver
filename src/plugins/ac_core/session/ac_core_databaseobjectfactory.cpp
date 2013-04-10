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

#include "ac_core_databaseobjectfactory.h"
#include "ac_core_controlcurve_modelitem.h"
#include "ac_core_controlgridline_modelitem.h"
#include "ac_core_curve_aggregate.h"
#include "ac_core_gridline_aggregate.h"
#include "ac_core_gridsettings_aggregate.h"
#include "ac_core_gridsettings_modelitem.h"
#include "ac_core_namespace.h"
#include "ac_core_note_aggregate.h"
#include "ac_core_note_modelitem.h"
#include "ac_core_pitchcurve_modelitem.h"
#include "ac_core_pitchgridline_modelitem.h"
#include "ac_core_projectsettings_aggregate.h"
#include "ac_core_projectsettings_modelitem.h"
#include "ac_core_score_aggregate.h"
#include "ac_core_score_modelitem.h"
#include "ac_core_timegridline_modelitem.h"
#include "ac_core_track_aggregate.h"
#include "ac_core_track_modelitem.h"
#include "ac_core_viewsettings_aggregate.h"
#include "ac_core_viewsettings_modelitem.h"
#include <mi_core_object_modelupdater.h>
#include <mi_core_objectlist_aggregate.h>
#include <mi_core_objectlist_modelitem.h>
#include <mi_core_objectlist_modelupdater.h>

using namespace Ac;

namespace Core {

IAggregate *DatabaseObjectFactory::create(int itemType, IAggregate *parent)
{
    IAggregate *aggregate = createAggregate(itemType, parent);
    if (!aggregate)
        return 0;
    createComponents(itemType, aggregate);
    aggregate->initialize();
    return aggregate;
}

IAggregate *DatabaseObjectFactory::createAggregate(int itemType, IAggregate *parent)
{
    switch (itemType) {
    case ControlCurveItem:
        return new Curve::Aggregate(parent);
    case ControlCurveListItem:
        return new ObjectList::Aggregate(parent, ControlCurveItem);
    case ControlGridLineItem:
        return new GridLine::Aggregate(parent);
    case ControlGridLineListItem:
        return new ObjectList::Aggregate(parent, ControlGridLineItem);
    case GridSettingsItem:
        return new GridSettings::Aggregate(parent);
    case NoteItem:
        return new Note::Aggregate(parent);
    case NoteListItem:
        return new ObjectList::Aggregate(parent, NoteItem);
    case PitchCurveItem:
        return new Curve::Aggregate(parent);
    case PitchGridLineItem:
        return new GridLine::Aggregate(parent);
    case PitchGridLineListItem:
        return new ObjectList::Aggregate(parent, PitchGridLineItem);
    case ProjectSettingsItem:
        return new ProjectSettings::Aggregate(parent);
    case ScoreItem:
        return new Score::Aggregate(parent);
    case TimeGridLineItem:
        return new GridLine::Aggregate(parent);
    case TimeGridLineListItem:
    case TrackItem:
        return new Track::Aggregate(parent);
    case TrackListItem:
        return new ObjectList::Aggregate(parent, TrackItem);
    case ViewSettingsItem:
        return new ViewSettings::Aggregate(parent);
    default:
        Q_ASSERT(0);
        return 0;
    }
}

void DatabaseObjectFactory::createComponents(int itemType, IAggregate *aggregate)
{
    switch (itemType) {
    case ControlCurveItem:
        new ControlCurve::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case ControlCurveListItem:
        new ObjectList::ModelItem(aggregate);
        new ObjectList::ModelUpdater(aggregate);
        break;
    case ControlGridLineItem:
        new ControlGridLine::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case ControlGridLineListItem:
        new ObjectList::ModelItem(aggregate);
        new ObjectList::ModelUpdater(aggregate);
        break;
    case GridSettingsItem:
        new GridSettings::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case NoteItem:
        new Note::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case NoteListItem:
        new ObjectList::ModelItem(aggregate);
        new ObjectList::ModelUpdater(aggregate);
        break;
    case PitchCurveItem:
        new PitchCurve::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case PitchGridLineItem:
        new PitchGridLine::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case PitchGridLineListItem:
        new ObjectList::ModelItem(aggregate);
        new ObjectList::ModelUpdater(aggregate);
        break;
    case ProjectSettingsItem:
        new ProjectSettings::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case ScoreItem:
        new Score::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case TimeGridLineItem:
        new TimeGridLine::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case TimeGridLineListItem:
        new ObjectList::ModelItem(aggregate);
        new ObjectList::ModelUpdater(aggregate);
        break;
    case TrackItem:
        new Track::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    case TrackListItem:
        new ObjectList::ModelItem(aggregate);
        new ObjectList::ModelUpdater(aggregate);
        break;
    case ViewSettingsItem:
        new ViewSettings::ModelItem(aggregate);
        new Object::ModelUpdater(aggregate);
        break;
    }
}

}
