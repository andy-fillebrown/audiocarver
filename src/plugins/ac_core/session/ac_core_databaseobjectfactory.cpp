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
#include <mi_core_modeldatawatcher.h>
#include <mi_core_modelitemlist.h>
#include <mi_core_modelitemwatcher.h>
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
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new Base::ModelItemWatcher(aggregate))->initialize();
        (new ControlCurve::ModelData(aggregate))->initialize();
        (new ControlCurve::ModelItem(aggregate))->initialize();
        break;
    case ControlCurveListItem:
        (new Base::ModelItemList(aggregate, ControlCurveItem))->initialize();
        break;
    case ControlGridLineItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new GridLine::ModelData(aggregate))->initialize();
        (new ControlGridLine::ModelItem(aggregate))->initialize();
        break;
    case ControlGridLineListItem:
        (new Base::ModelItemList(aggregate, ControlGridLineItem))->initialize();
        break;
    case GridSettingsItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new GridSettings::ModelData(aggregate))->initialize();
        (new GridSettings::ModelItem(aggregate))->initialize();
        break;
    case NoteItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new ScoreObject::ModelData(aggregate))->initialize();
        (new Note::ModelItem(aggregate))->initialize();
        break;
    case NoteListItem:
        (new Base::ModelItemList(aggregate, NoteItem))->initialize();
        break;
    case PitchCurveItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new PitchCurve::ModelData(aggregate))->initialize();
        (new PitchCurve::ModelItem(aggregate))->initialize();
        break;
    case PitchGridLineItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new GridLine::ModelData(aggregate))->initialize();
        (new PitchGridLine::ModelItem(aggregate))->initialize();
        break;
    case PitchGridLineListItem:
        (new Base::ModelItemList(aggregate, PitchGridLineItem))->initialize();
        break;
    case ProjectSettingsItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new ProjectSettings::ModelData(aggregate))->initialize();
        (new ProjectSettings::ModelItem(aggregate))->initialize();
        break;
    case ScoreItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new Score::ModelData(aggregate))->initialize();
        (new Score::ModelItem(aggregate))->initialize();
        break;
    case TimeGridLineItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new GridLine::ModelData(aggregate))->initialize();
        (new TimeGridLine::ModelItem(aggregate))->initialize();
        break;
    case TimeGridLineListItem:
        (new Base::ModelItemList(aggregate, TimeGridLineItem))->initialize();
        break;
    case TrackItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new Base::ModelItemWatcher(aggregate))->initialize();
        (new Track::ModelData(aggregate))->initialize();
        (new Track::ModelItem(aggregate))->initialize();
        break;
    case TrackListItem:
        (new Base::ModelItemList(aggregate, TrackItem))->initialize();
        break;
    case ViewSettingsItem:
        (new Base::ModelDataWatcher(aggregate))->initialize();
        (new ViewSettings::ModelData(aggregate))->initialize();
        (new ViewSettings::ModelItem(aggregate))->initialize();
        break;
    default:
        return 0;
    }
    if (parent)
        query<IModelItem>(aggregate)->setParent(parent);
    return aggregate;
}

}
