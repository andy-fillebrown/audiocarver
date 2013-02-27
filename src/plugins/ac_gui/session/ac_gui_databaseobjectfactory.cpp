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

#include "ac_gui_databaseobjectfactory.h"
#include "ac_gui_controlcurve_graphicsdata.h"
#include "ac_gui_controlgridline_graphicsdata.h"
#include "ac_gui_gridsettings_graphicsdata.h"
#include "ac_gui_namespace.h"
#include "ac_gui_note_graphicsdata.h"
#include "ac_gui_note_graphicsitemupdater.h"
#include "ac_gui_note_modelitem.h"
#include "ac_gui_object_graphicsdataupdater.h"
#include "ac_gui_object_graphicsitem.h"
#include "ac_gui_object_graphicsitemupdater.h"
#include "ac_gui_pitchcurve_graphicsdata.h"
#include "ac_gui_pitchgridline_graphicsdata.h"
#include "ac_gui_score_graphicsdata.h"
#include "ac_gui_timegridline_graphicsdata.h"
#include "ac_gui_track_graphicsdata.h"
#include "ac_gui_tracklist_graphicsdataupdater.h"
#include "ac_gui_velocity_graphicsdata.h"
#include "ac_gui_velocity_modelitem.h"
#include <ac_core_scoreobject_modeldata.h>
#include <mi_core_aggregate.h>
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
        Core::DatabaseObjectFactory::create(itemType, aggregate);
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
    case NoteItem:
        new Note::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        new Note::GraphicsItemUpdater(aggregate);
        new ScoreObject::ModelData(aggregate);
        new Note::Gui::ModelItem(aggregate);
        break;
    case PitchCurveItem:
        new PitchCurve::GraphicsData(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        Core::DatabaseObjectFactory::create(itemType, aggregate);
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
