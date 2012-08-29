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
#include "ac_gui_controlcurve_subentity.h"
#include "ac_gui_controlgridline_entity.h"
#include "ac_gui_curve_entity.h"
#include "ac_gui_curve_graphicsitem.h"
#include "ac_gui_gridsettings_entity.h"
#include "ac_gui_note_entity.h"
#include "ac_gui_pitchcurve_graphicsitem.h"
#include "ac_gui_pitchcurve_subentity.h"
#include "ac_gui_pitchgridline_entity.h"
#include "ac_gui_score_entity.h"
#include "ac_gui_timegridline_entity.h"
#include <ac_core_namespace.h>

using namespace Ac;

namespace Gui {

IUnknown *DatabaseObjectFactory::initialize()
{
    return Core::DatabaseObjectFactory::initialize();
}

IAggregate *DatabaseObjectFactory::create(int itemType, IModelItem *parent)
{
    IAggregate *aggregate = Core::DatabaseObjectFactory::create(itemType, parent);
    switch (itemType) {
    case ControlCurveItem:
        (new Curve::Entity(aggregate))->initialize();
        (new ControlCurve::SubEntity(aggregate))->initialize();
        (new ControlCurve::GraphicsItem(aggregate))->initialize();
        break;
    case ControlGridLineItem:
        (new ControlGridLine::Entity(aggregate))->initialize();
        break;
    case GridSettingsItem:
        (new GridSettings::Entity(aggregate))->initialize();
        break;
    case NoteItem:
        (new Note::Entity(aggregate))->initialize();
        break;
    case PitchCurveItem:
        (new Curve::Entity(aggregate))->initialize();
        (new PitchCurve::SubEntity(aggregate))->initialize();
        (new PitchCurve::GraphicsItem(aggregate))->initialize();
        break;
    case PitchGridLineItem:
        (new PitchGridLine::Entity(aggregate))->initialize();
        break;
    case ScoreItem:
        (new Score::Entity(aggregate))->initialize();
        break;
    case TimeGridLineItem:
        (new TimeGridLine::Entity(aggregate))->initialize();
        break;
    case TrackItem:
        (new ScoreObject::Entity(aggregate))->initialize();
        break;
    }
    return aggregate;
}

}
