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

#include "ac_gui_dataobjectfactory.h"

#include <ac_gui_database.h>
#include <ac_gui_controlcurve.h>
#include <ac_gui_graphicsobject.h>
#include <ac_gui_note.h>
#include <ac_gui_pitchcurve.h>
#include <ac_gui_score.h>
#include <ac_gui_track.h>

#include <mi_core_superaggregator.h>

using namespace Mi::Core;

namespace Ac {
namespace Gui {

DataObjectFactory::DataObjectFactory(Database *aggregator)
    :   Core::DataObjectFactory(aggregator)
{}

IAggregate *DataObjectFactory::init()
{
    return Core::DataObjectFactory::init();
}

IAggregator *DataObjectFactory::create(int itemType, IModelItem *parent)
{
    SuperAggregator *super_aggregator = dynamic_cast<SuperAggregator*>(Core::DataObjectFactory::create(itemType, parent));
    GraphicsObject *graphics_object = 0;
    switch (itemType) {
    case ControlCurveItem:
        graphics_object = new ControlCurve;
        break;
    case NoteItem:
        graphics_object = new Note;
        break;
    case PitchCurveItem:
        graphics_object = new PitchCurve;
        break;
    case ScoreItem:
        graphics_object = new Score;
        break;
    case TrackItem:
        graphics_object = new Track;
        break;
    }
    if (graphics_object) {
        super_aggregator->appendSubAggregator(graphics_object);
        graphics_object->init();
    }
    return super_aggregator;
}

} // namespace Core
} // namespace Ac
