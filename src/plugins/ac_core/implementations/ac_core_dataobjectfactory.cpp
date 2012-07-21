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

#include "ac_core_dataobjectfactory.h"

#include <mi_imodelitem.h>

#include <ac_core_database.h>
#include <ac_core_dataobjectlist.h>
#include <ac_core_controlcurve.h>
#include <ac_core_gridline.h>
#include <ac_core_gridsettings.h>
#include <ac_core_note.h>
#include <ac_core_pitchcurve.h>
#include <ac_core_projectsettings.h>
#include <ac_core_score.h>
#include <ac_core_track.h>
#include <ac_core_viewsettings.h>

namespace Ac {
namespace Core {

IAggregate *DataObjectFactory::init()
{
    return this;
}

IAggregator *DataObjectFactory::create(int itemType, IModelItem *parent)
{
    IAggregator *aggregator = 0;
    switch (itemType) {
    case ControlCurveItem:
        aggregator = (new ControlCurve)->init();
        break;
    case ControlCurveListItem:
        aggregator = (new DataObjectList(ControlCurveItem))->init();
        break;
    case ControlGridLineItem:
        aggregator = (new ControlGridLine)->init();
        break;
    case ControlGridLineListItem:
        aggregator = (new DataObjectList(ControlGridLineItem))->init();
        break;
    case GridSettingsItem:
        aggregator = (new GridSettings)->init();
        break;
    case NoteItem:
        aggregator = (new Note)->init();
        break;
    case NoteListItem:
        aggregator = (new DataObjectList(NoteItem))->init();
        break;
    case PitchCurveItem:
        aggregator = (new PitchCurve)->init();
        break;
    case PitchGridLineItem:
        aggregator = (new PitchGridLine)->init();
        break;
    case PitchGridLineListItem:
        aggregator = (new DataObjectList(PitchGridLineItem))->init();
        break;
    case ProjectSettingsItem:
        aggregator = (new ProjectSettings)->init();
        break;
    case ScoreItem:
        aggregator = (new Score)->init();
        break;
    case TimeGridLineItem:
        aggregator = (new TimeGridLine)->init();
        break;
    case TimeGridLineListItem:
        aggregator = (new DataObjectList(TimeGridLineItem))->init();
        break;
    case TrackItem:
        aggregator = (new Track)->init();
        break;
    case TrackListItem:
        aggregator = (new DataObjectList(TrackItem))->init();
        break;
    case ViewSettingsItem:
        aggregator = (new ViewSettings)->init();
        break;
    default:
        return 0;
    }
    if (parent)
        query<IModelItem>(aggregator)->setParent(parent);
    return aggregator;
}

IAggregator *DataObjectFactory::aggregator() const
{
    return _aggregator;
}

} // namespace Core
} // namespace Ac
