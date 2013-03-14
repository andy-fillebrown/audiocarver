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
#include "ac_core_controlcurve_modeldata.h"
#include "ac_core_controlcurve_modeliteminfo.h"
#include "ac_core_controlgridline_modeliteminfo.h"
#include "ac_core_gridline_modeldata.h"
#include "ac_core_gridsettings_modeldata.h"
#include "ac_core_gridsettings_modelitem.h"
#include "ac_core_gridsettings_modeliteminfo.h"
#include "ac_core_namespace.h"
#include "ac_core_note_modeliteminfo.h"
#include "ac_core_pitchcurve_modeldata.h"
#include "ac_core_pitchcurve_modeliteminfo.h"
#include "ac_core_pitchgridline_modeliteminfo.h"
#include <ac_core_point.h>
#include "ac_core_projectsettings_modeldata.h"
#include "ac_core_projectsettings_modeliteminfo.h"
#include "ac_core_score_modeldata.h"
#include "ac_core_score_modelitem.h"
#include "ac_core_score_modeliteminfo.h"
#include "ac_core_scoreobject_modelitem.h"
#include "ac_core_timegridline_modeliteminfo.h"
#include "ac_core_track_modeldata.h"
#include "ac_core_track_modelitem.h"
#include "ac_core_track_modeliteminfo.h"
#include "ac_core_viewsettings_modeldata.h"
#include "ac_core_viewsettings_modelitem.h"
#include "ac_core_viewsettings_modeliteminfo.h"
#include <mi_core_base_aggregate.h>
#include <mi_core_object_modeldataupdater.h>
#include <mi_core_objectlist_modeldata.h>
#include <mi_core_objectlist_modelitem.h>
#include <mi_core_objectlist_modeliteminfo.h>
#include <mi_core_objectlist_modelitemlistupdater.h>
#include <imodelitem.h>

using namespace Ac;

namespace Core {

IAggregate *DatabaseObjectFactory::create(int itemType, IModelItem *parent)
{
    IAggregate *aggregate = new Base::Aggregate;
    create(itemType, aggregate);
    if (parent)
        QUERY(IModelItem, aggregate)->setParent(parent);
    aggregate->initialize();
    return aggregate;
}

IAggregate *DatabaseObjectFactory::create(int itemType, IAggregate *aggregate)
{
    switch (itemType) {
    case ControlCurveItem:
        new ControlCurve::ModelItemInfo(aggregate);
        new Object::ModelItem(aggregate);
        new ControlCurve::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case ControlCurveListItem:
        new ObjectList::ModelItemInfo(aggregate);
        new ObjectList::ModelItem(aggregate, ControlCurveItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListUpdater(aggregate);
        break;
    case ControlGridLineItem:
        new ControlGridLine::ModelItemInfo(aggregate);
        new Object::ModelItem(aggregate);
        new GridLine::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case ControlGridLineListItem:
        new ObjectList::ModelItemInfo(aggregate);
        new ObjectList::ModelItem(aggregate, ControlGridLineItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListUpdater(aggregate);
        break;
    case GridSettingsItem:
        new GridSettings::ModelItemInfo(aggregate);
        new GridSettings::ModelItem(aggregate);
        new GridSettings::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case NoteItem:
        new Note::ModelItemInfo(aggregate);
        new ScoreObject::ModelItem(aggregate);
        new ScoreObject::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case NoteListItem:
        new ObjectList::ModelItemInfo(aggregate);
        new ObjectList::ModelItem(aggregate, NoteItem);
        new ObjectList::ModelItemListUpdater(aggregate);
        break;
    case PitchCurveItem:
        new PitchCurve::ModelItemInfo(aggregate);
        new Object::ModelItem(aggregate);
        new PitchCurve::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case PitchGridLineItem:
        new PitchGridLine::ModelItemInfo(aggregate);
        new Object::ModelItem(aggregate);
        new GridLine::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case PitchGridLineListItem:
        new ObjectList::ModelItemInfo(aggregate);
        new ObjectList::ModelItem(aggregate, PitchGridLineItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListUpdater(aggregate);
        break;
    case ProjectSettingsItem:
        new ProjectSettings::ModelItemInfo(aggregate);
        new Object::ModelItem(aggregate);
        new ProjectSettings::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case ScoreItem:
        new Score::ModelItemInfo(aggregate);
        new Score::ModelItem(aggregate);
        new Score::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case TimeGridLineItem:
        new TimeGridLine::ModelItemInfo(aggregate);
        new Object::ModelItem(aggregate);
        new GridLine::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case TimeGridLineListItem:
        new ObjectList::ModelItemInfo(aggregate);
        new ObjectList::ModelItem(aggregate, TimeGridLineItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListUpdater(aggregate);
        break;
    case TrackItem:
        new Track::ModelItemInfo(aggregate);
        new Track::ModelItem(aggregate);
        new Track::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case TrackListItem:
        new ObjectList::ModelItemInfo(aggregate);
        new ObjectList::ModelItem(aggregate, TrackItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListUpdater(aggregate);
        break;
    case ViewSettingsItem:
        new ViewSettings::ModelItemInfo(aggregate);
        new ViewSettings::ModelItem(aggregate);
        new ViewSettings::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    default:
        Q_ASSERT(0);
        delete aggregate;
        return 0;
    }
    return aggregate;
}

}
