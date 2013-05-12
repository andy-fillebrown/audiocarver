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
#include "ac_gui_controlcurve_graphicsitem.h"
#include "ac_gui_controlgridline_graphicsitem.h"
#include "ac_gui_curve_graphicsdelegate.h"
#include "ac_gui_curve_graphicsgriplist.h"
#include "ac_gui_gridsettings_graphicsitem.h"
#include "ac_gui_grip_graphicsitem.h"
#include "ac_gui_namespace.h"
#include "ac_gui_note_graphicsitem.h"
#include "ac_gui_note_graphicsupdater.h"
#include "ac_gui_object_graphicsgrip.h"
#include "ac_gui_object_graphicsitem.h"
#include "ac_gui_object_graphicsupdater.h"
#include "ac_gui_objectlist_graphicsitem.h"
#include "ac_gui_pitchcurve_graphicsitem.h"
#include "ac_gui_pitchgridline_graphicsitem.h"
#include "ac_gui_score_graphicsitem.h"
#include "ac_gui_score_graphicsupdater.h"
#include "ac_gui_timegridline_graphicsitem.h"
#include "ac_gui_track_graphicsitem.h"
#include "ac_gui_tracklist_graphicsupdater.h"
#include "ac_gui_velocity_graphicsdelegate.h"
#include "ac_gui_velocity_graphicsgriplist.h"
#include "ac_gui_velocity_graphicsitem.h"
#include <mi_core_object_aggregate.h>
#include <mi_core_object_modelitem.h>

namespace Ac {
namespace Gui {

void DatabaseObjectFactory::createComponents(int itemType, IAggregate *aggregate)
{
    Core::DatabaseObjectFactory::createComponents(itemType, aggregate);
    switch (itemType) {
    case ControlCurveItem:
        new ControlCurve::GraphicsItem(aggregate);
        new Curve::GraphicsGripList(aggregate);
        new Curve::GraphicsDelegate(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    case ControlGridLineItem:
        new ControlGridLine::GraphicsItem(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    case GridSettingsItem:
        new GridSettings::GraphicsItem(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    case GripItem:
        new Object::ModelItem(aggregate);
        new Grip::GraphicsItem(aggregate);
        new Object::GraphicsGrip(aggregate);
        break;
    case NoteItem:
        new Note::GraphicsItem(aggregate);
        new Note::GraphicsUpdater(aggregate);
        break;
    case NoteListItem:
        new ObjectList::GraphicsItem(aggregate);
        break;
    case PitchCurveItem:
        new PitchCurve::GraphicsItem(aggregate);
        new Curve::GraphicsGripList(aggregate);
        new Curve::GraphicsDelegate(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    case PitchGridLineItem:
        new PitchGridLine::GraphicsItem(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    case ScoreItem:
        new Score::GraphicsItem(aggregate);
        new Score::GraphicsUpdater(aggregate);
        break;
    case TimeGridLineItem:
        new TimeGridLine::GraphicsItem(aggregate);
        new Object::GraphicsItem(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    case TrackItem:
        new Track::GraphicsItem(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    case TrackListItem:
        new TrackList::GraphicsUpdater(aggregate);
        break;
    case VelocityItem:
        new Object::ModelItem(aggregate);
        new Velocity::GraphicsItem(aggregate);
        new Velocity::GraphicsGripList(aggregate);
        new Velocity::GraphicsDelegate(aggregate);
        new Object::GraphicsUpdater(aggregate);
        break;
    }
}

}
}
