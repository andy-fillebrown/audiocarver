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

#include "ac_database_gui_objectfactory.h"

#include <ac_database_gui_controlcurve.h>
#include <ac_database_gui_note.h>
#include <ac_database_gui_pitchcurve.h>

namespace Database {
namespace Gui {

IAggregator *ObjectFactory::createObject(int itemType)
{
    switch (itemType) {
    case Ac::ControlCurveItem:
        return Q_NEW_OBJECT(ControlCurve);
    case Ac::NoteItem:
        return Q_NEW_OBJECT(Note);
    case Ac::PitchCurveItem:
        return Q_NEW_OBJECT(PitchCurve);
    default:
        return Database::ObjectFactory::createObject(itemType);
    }
}

} // namespace Gui
} // namespace Database
