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
#include <mi_core_objectlist_modelitemlistwatcher.h>
#include <imodelitem.h>

using namespace Ac;

namespace Core {

IAggregate *DatabaseObjectFactory::create(int itemType, IModelItem *parent)
{
    IAggregate *aggregate = new Base::Aggregate;
    create(itemType, aggregate);
    if (parent)
        query<IModelItem>(aggregate)->setParent(parent);
    aggregate->initialize();
    return aggregate;
}

IAggregate *DatabaseObjectFactory::create(int itemType, IAggregate *aggregate)
{
    switch (itemType) {
    case ControlCurveItem:
        new ControlCurve::ModelItem(aggregate);
        new ControlCurve::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case ControlCurveListItem:
        new ObjectList::ModelItem(aggregate, ControlCurveItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListWatcher(aggregate);
        break;
    case ControlGridLineItem:
        new ControlGridLine::ModelItem(aggregate);
        new GridLine::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case ControlGridLineListItem:
        new ObjectList::ModelItem(aggregate, ControlGridLineItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListWatcher(aggregate);
        break;
    case GridSettingsItem:
        new GridSettings::ModelItem(aggregate);
        new GridSettings::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case NoteItem:
        new Note::ModelItem(aggregate);
        new ScoreObject::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case NoteListItem:
        new ObjectList::ModelItem(aggregate, NoteItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListWatcher(aggregate);
        break;
    case PitchCurveItem:
        new PitchCurve::ModelItem(aggregate);
        new PitchCurve::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case PitchGridLineItem:
        new PitchGridLine::ModelItem(aggregate);
        new GridLine::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case PitchGridLineListItem:
        new ObjectList::ModelItem(aggregate, PitchGridLineItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListWatcher(aggregate);
        break;
    case ProjectSettingsItem:
        new ProjectSettings::ModelItem(aggregate);
        new ProjectSettings::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case ScoreItem:
        new Score::ModelItem(aggregate);
        new Score::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case TimeGridLineItem:
        new TimeGridLine::ModelItem(aggregate);
        new GridLine::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case TimeGridLineListItem:
        new ObjectList::ModelItem(aggregate, TimeGridLineItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListWatcher(aggregate);
        break;
    case TrackItem:
        new Track::ModelItem(aggregate);
        new Track::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    case TrackListItem:
        new ObjectList::ModelItem(aggregate, TrackItem);
        new ObjectList::ModelData(aggregate);
        new ObjectList::ModelItemListWatcher(aggregate);
        break;
    case ViewSettingsItem:
        new ViewSettings::ModelItem(aggregate);
        new ViewSettings::ModelData(aggregate);
        new Object::ModelDataWatcher(aggregate);
        break;
    default:
        Q_ASSERT(0);
        delete aggregate;
        return 0;
    }
    return aggregate;
}

}
