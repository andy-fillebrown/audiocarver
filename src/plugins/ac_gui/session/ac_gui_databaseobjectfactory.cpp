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

#include "ac_gui_databaseobjectfactory.h"
#include "ac_gui_controlcurve_graphicsdata.h"
#include "ac_gui_controlcurve_modelitem.h"
#include "ac_gui_controlgridline_graphicsdata.h"
#include "ac_gui_gridsettings_graphicsdata.h"
#include "ac_gui_grip_modelitem.h"
#include "ac_gui_namespace.h"
#include "ac_gui_note_graphicsdata.h"
#include "ac_gui_note_graphicsitemupdater.h"
#include "ac_gui_note_modelitem.h"
#include "ac_gui_object_graphicsdataupdater.h"
#include "ac_gui_object_graphicsitem.h"
#include "ac_gui_object_graphicsitemupdater.h"
#include "ac_gui_pitchcurve_graphicsdata.h"
#include "ac_gui_pitchcurve_modelitem.h"
#include "ac_gui_pitchgridline_graphicsdata.h"
#include "ac_gui_score_graphicsdata.h"
#include "ac_gui_timegridline_graphicsdata.h"
#include "ac_gui_track_graphicsdata.h"
#include "ac_gui_tracklist_graphicsdataupdater.h"
#include "ac_gui_velocity_graphicsdata.h"
#include "ac_gui_velocity_modelitem.h"
#include <ac_core_controlcurve_modeldata.h>
#include <ac_core_pitchcurve_modeldata.h>
#include <ac_core_scoreobject_modeldata.h>
#include <mi_core_base_aggregate.h>
#include <mi_core_object_modeldataupdater.h>
#include <mi_core_objectlist_modeldata.h>
#include <mi_core_objectlist_modelitem.h>
#include <imodelitem.h>

using namespace Ac;

namespace Gui {

IAggregate *DatabaseObjectFactory::create(int itemType, IAggregate *aggregate)
{
    switch (itemType) {
    case ControlCurveItem:
        new ControlCurve::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        new ControlCurve::Gui::ModelItem(aggregate);
        new ControlCurve::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case ControlGridLineItem:
        new ControlGridLine::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case GridSettingsItem:
        new GridSettings::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case GripItem:
        new Grip::ModelItem(aggregate);
        break;
    case GripListItem:
        new ObjectList::ModelItem(aggregate, GripItem);
        new ObjectList::ModelData(aggregate);
        break;
    case NoteItem:
        new Note::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        new Note::GraphicsItemUpdater(aggregate);
        new ScoreObject::ModelData(aggregate);
        new Note::Gui::ModelItem(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case PitchCurveItem:
        new PitchCurve::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        new PitchCurve::Gui::ModelItem(aggregate);
        new PitchCurve::ModelData(aggregate);
        new Object::ModelDataUpdater(aggregate);
        break;
    case PitchGridLineItem:
        new PitchGridLine::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case ScoreItem:
        new Score::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case TimeGridLineItem:
        new TimeGridLine::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case TrackItem:
        new Track::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case TrackListItem:
        new TrackList::GraphicsDataUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case VelocityItem:
        new Velocity::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Velocity::ModelItem(aggregate);
        break;
    default:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
    }
    return aggregate;
}

}
