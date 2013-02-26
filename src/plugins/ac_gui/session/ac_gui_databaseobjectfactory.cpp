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
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new ControlCurve::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        break;
    case ControlGridLineItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new ControlGridLine::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        break;
    case GridSettingsItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new GridSettings::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        break;
    case NoteItem:
        new Note::Gui::ModelItem(aggregate);
        new ScoreObject::ModelData(aggregate);
        new Note::GraphicsData(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        new Note::GraphicsItemUpdater(aggregate);
        break;
    case PitchCurveItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new PitchCurve::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        break;
    case PitchGridLineItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new PitchGridLine::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        break;
    case ScoreItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new Score::GraphicsData(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        break;
    case TimeGridLineItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new TimeGridLine::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        break;
    case TrackItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new Track::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        new Object::GraphicsDataUpdater(aggregate);
        break;
    case TrackListItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        new TrackList::GraphicsDataUpdater(aggregate);
        break;
    case VelocityItem:
        new Velocity::ModelItem(aggregate);
        new Velocity::GraphicsData(aggregate);
        new Object::GraphicsItemUpdater(aggregate);
        break;
    default:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
    }
    return aggregate;
}

}
