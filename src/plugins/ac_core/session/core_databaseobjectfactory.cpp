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

#include "core_databaseobjectfactory.h"
#include "ac_core_namespace.h"
#include "database/controlcurve_modeldata.h"
#include "database/controlcurve_modelitem.h"
#include "database/controlgridline_modelitem.h"
#include "database/gridline_modeldata.h"
#include "database/gridsettings_modeldata.h"
#include "database/gridsettings_modelitem.h"
#include "database/note_modelitem.h"
#include "database/pitchcurve_modeldata.h"
#include "database/pitchcurve_modelitem.h"
#include "database/pitchgridline_modelitem.h"
#include "database/projectsettings_modeldata.h"
#include "database/projectsettings_modelitem.h"
#include "database/score_modeldata.h"
#include "database/score_modelitem.h"
#include "database/timegridline_modelitem.h"
#include "database/track_modeldata.h"
#include "database/track_modelitem.h"
#include "database/viewsettings_modeldata.h"
#include "database/viewsettings_modelitem.h"
#include <base/aggregate.h>
#include <base/modelitemlist.h>
#include <imodelitem.h>
#include <tools/point.h>

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
        (new ControlCurve::ModelData(aggregate))->initialize();
        (new ControlCurve::ModelItem(aggregate))->initialize();
        break;
    case ControlCurveListItem:
        (new Base::ModelItemList(aggregate, ControlCurveItem))->initialize();
        break;
    case ControlGridLineItem:
        (new GridLine::ModelData(aggregate))->initialize();
        (new ControlGridLine::ModelItem(aggregate))->initialize();
        break;
    case ControlGridLineListItem:
        (new Base::ModelItemList(aggregate, ControlGridLineItem))->initialize();
        break;
    case GridSettingsItem:
        (new GridSettings::ModelData(aggregate))->initialize();
        (new GridSettings::ModelItem(aggregate))->initialize();
        break;
    case NoteItem:
        (new ScoreObject::ModelData(aggregate))->initialize();
        (new Note::ModelItem(aggregate))->initialize();
        break;
    case NoteListItem:
        (new Base::ModelItemList(aggregate, NoteItem))->initialize();
        break;
    case PitchCurveItem:
        (new PitchCurve::ModelData(aggregate))->initialize();
        (new PitchCurve::ModelItem(aggregate))->initialize();
        break;
    case PitchGridLineItem:
        (new GridLine::ModelData(aggregate))->initialize();
        (new PitchGridLine::ModelItem(aggregate))->initialize();
        break;
    case PitchGridLineListItem:
        (new Base::ModelItemList(aggregate, PitchGridLineItem))->initialize();
        break;
    case ProjectSettingsItem:
        (new ProjectSettings::ModelData(aggregate))->initialize();
        (new ProjectSettings::ModelItem(aggregate))->initialize();
        break;
    case ScoreItem:
        (new Score::ModelData(aggregate))->initialize();
        (new Score::ModelItem(aggregate))->initialize();
        break;
    case TimeGridLineItem:
        (new GridLine::ModelData(aggregate))->initialize();
        (new TimeGridLine::ModelItem(aggregate))->initialize();
        break;
    case TimeGridLineListItem:
        (new Base::ModelItemList(aggregate, TimeGridLineItem))->initialize();
        break;
    case TrackItem:
        (new Track::ModelData(aggregate))->initialize();
        (new Track::ModelItem(aggregate))->initialize();
        break;
    case TrackListItem:
        (new Base::ModelItemList(aggregate, TrackItem))->initialize();
        break;
    case ViewSettingsItem:
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
