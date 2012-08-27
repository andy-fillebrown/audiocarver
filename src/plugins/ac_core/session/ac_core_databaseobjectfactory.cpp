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

#include "ac_core_databaseobjectfactory.h"
#include "ac_core_controlcurve_modeldata.h"
#include "ac_core_controlcurve_modelitem.h"
#include "ac_core_controlgridline_modelitem.h"
#include "ac_core_gridline_modeldata.h"
#include "ac_core_gridsettings_modeldata.h"
#include "ac_core_gridsettings_modelitem.h"
#include "ac_core_namespace.h"
#include "ac_core_note_modelitem.h"
#include "ac_core_pitchcurve_modeldata.h"
#include "ac_core_pitchcurve_modelitem.h"
#include "ac_core_pitchgridline_modelitem.h"
#include <ac_core_point.h>
#include "ac_core_projectsettings_modeldata.h"
#include "ac_core_projectsettings_modelitem.h"
#include "ac_core_score_modeldata.h"
#include "ac_core_score_modelitem.h"
#include "ac_core_timegridline_modelitem.h"
#include "ac_core_track_modeldata.h"
#include "ac_core_track_modelitem.h"
#include "ac_core_viewsettings_modeldata.h"
#include "ac_core_viewsettings_modelitem.h"
#include <mi_core_aggregate.h>
#include <mi_core_object_modeldatawatcher.h>
#include <mi_core_objectlist_modeldata.h>
#include <mi_core_objectlist_modelitem.h>
#include <mi_core_objectlist_modelitemwatcher.h>
#include <imodelitem.h>

using namespace Ac;

namespace Core {

IUnknown *DatabaseObjectFactory::initialize()
{
    return Base::DatabaseObjectFactory::initialize();
}

IAggregate *DatabaseObjectFactory::create(int itemType, IModelItem *parent)
{
    IAggregate *aggregate = (new Base::Aggregate)->initialize();
    switch (itemType) {
    case ControlCurveItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new ControlCurve::ModelData(aggregate))->initialize();
        (new ControlCurve::ModelItem(aggregate))->initialize();
        break;
    case ControlCurveListItem:
        (new ObjectList::ModelItemWatcher(aggregate))->initialize();
        (new ObjectList::ModelItem(aggregate, ControlCurveItem))->initialize();
        (new ObjectList::ModelData(aggregate))->initialize();
        break;
    case ControlGridLineItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new ControlGridLine::ModelItem(aggregate))->initialize();
        (new GridLine::ModelData(aggregate))->initialize();
        break;
    case ControlGridLineListItem:
        (new ObjectList::ModelItemWatcher(aggregate))->initialize();
        (new ObjectList::ModelItem(aggregate, ControlGridLineItem))->initialize();
        (new ObjectList::ModelData(aggregate))->initialize();
        break;
    case GridSettingsItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new GridSettings::ModelItem(aggregate))->initialize();
        (new GridSettings::ModelData(aggregate))->initialize();
        break;
    case NoteItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new Note::ModelItem(aggregate))->initialize();
        (new ScoreObject::ModelData(aggregate))->initialize();
        break;
    case NoteListItem:
        (new ObjectList::ModelItemWatcher(aggregate))->initialize();
        (new ObjectList::ModelItem(aggregate, NoteItem))->initialize();
        (new ObjectList::ModelData(aggregate))->initialize();
        break;
    case PitchCurveItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new PitchCurve::ModelData(aggregate))->initialize();
        (new PitchCurve::ModelItem(aggregate))->initialize();
        break;
    case PitchGridLineItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new PitchGridLine::ModelItem(aggregate))->initialize();
        (new GridLine::ModelData(aggregate))->initialize();
        break;
    case PitchGridLineListItem:
        (new ObjectList::ModelItemWatcher(aggregate))->initialize();
        (new ObjectList::ModelItem(aggregate, PitchGridLineItem))->initialize();
        (new ObjectList::ModelData(aggregate))->initialize();
        break;
    case ProjectSettingsItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new ProjectSettings::ModelItem(aggregate))->initialize();
        (new ProjectSettings::ModelData(aggregate))->initialize();
        break;
    case ScoreItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new Score::ModelItem(aggregate))->initialize();
        (new Score::ModelData(aggregate))->initialize();
        break;
    case TimeGridLineItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new TimeGridLine::ModelItem(aggregate))->initialize();
        (new GridLine::ModelData(aggregate))->initialize();
        break;
    case TimeGridLineListItem:
        (new ObjectList::ModelItemWatcher(aggregate))->initialize();
        (new ObjectList::ModelItem(aggregate, TimeGridLineItem))->initialize();
        (new ObjectList::ModelData(aggregate))->initialize();
        break;
    case TrackItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new Track::ModelItem(aggregate))->initialize();
        (new Track::ModelData(aggregate))->initialize();
        break;
    case TrackListItem:
        (new ObjectList::ModelItemWatcher(aggregate))->initialize();
        (new ObjectList::ModelItem(aggregate, TrackItem))->initialize();
        (new ObjectList::ModelData(aggregate))->initialize();
        break;
    case ViewSettingsItem:
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new ViewSettings::ModelItem(aggregate))->initialize();
        (new ViewSettings::ModelData(aggregate))->initialize();
        break;
    default:
        return 0;
    }
    if (parent)
        query<IModelItem>(aggregate)->setParent(parent);
    return aggregate;
}

}
