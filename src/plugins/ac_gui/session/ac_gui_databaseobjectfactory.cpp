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
#include "ac_gui_controlcurve_graphicsitem.h"
#include "ac_gui_controlgridline_graphicsitem.h"
#include "ac_gui_curve_graphicsitem.h"
#include "ac_gui_gridsettings_graphicsitem.h"
#include "ac_gui_namespace.h"
#include "ac_gui_note_entity.h"
#include "ac_gui_note_graphicsitem.h"
#include "ac_gui_note_modelitem.h"
#include "ac_gui_note_modelitemwatcher.h"
#include "ac_gui_object_modeldatawatcher.h"
#include "ac_gui_object_modelitemwatcher.h"
#include "ac_gui_pitchcurve_graphicsitem.h"
#include "ac_gui_pitchgridline_graphicsitem.h"
#include "ac_gui_score_graphicsitem.h"
#include "ac_gui_timegridline_graphicsitem.h"
#include "ac_gui_tracklist_modelitemlistwatcher.h"
#include "ac_gui_velocity_graphicsitem.h"
#include "ac_gui_velocity_modelitem.h"
#include <ac_core_scoreobject_modeldata.h>
#include <mi_core_aggregate.h>
#include <imodelitem.h>

using namespace Ac;

inline IAggregate *setAggregateParent(IAggregate *child, IModelItem *parent)
{
    query<IModelItem>(child)->setParent(parent);
    return child;
}

namespace Gui {

IUnknown *DatabaseObjectFactory::initialize()
{
    return Core::DatabaseObjectFactory::initialize();
}

IAggregate *DatabaseObjectFactory::create(int itemType, IAggregate *aggregate)
{
    switch (itemType) {
    case ControlCurveItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new ControlCurve::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        break;
    case ControlGridLineItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new ControlGridLine::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        break;
    case GridSettingsItem:
        (new GridSettings::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        break;
    case NoteItem:
        (new ScoreObject::ModelData(aggregate))->initialize();
        (new Note::GraphicsItem(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        (new Note::ModelItemWatcher(aggregate))->initialize();
        (new Note::Gui::ModelItem(aggregate))->initialize();
        break;
    case PitchCurveItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new PitchCurve::GraphicsItem(aggregate))->initialize();
        (new PitchCurve::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        break;
    case PitchGridLineItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new PitchGridLine::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        break;
    case ScoreItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new Score::GraphicsItem(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        break;
    case TimeGridLineItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new TimeGridLine::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        break;
    case TrackItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new ScoreObject::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        (new Object::ModelDataWatcher(aggregate))->initialize();
        break;
    case TrackListItem:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
        (new TrackList::ModelItemListWatcher(aggregate))->initialize();
        break;
    case VelocityItem:
        (new Velocity::ModelItem(aggregate))->initialize();
        (new Velocity::GraphicsItem(aggregate))->initialize();
        (new Object::ModelItemWatcher(aggregate))->initialize();
        break;
    default:
        Core::DatabaseObjectFactory::create(itemType, aggregate);
    }
    return aggregate;
}

}
