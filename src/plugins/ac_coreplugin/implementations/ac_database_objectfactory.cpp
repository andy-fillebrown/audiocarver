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

#include "ac_database_objectfactory.h"

#include <ac_database_controlcurve.h>
#include <ac_database_note.h>
#include <ac_database_pitchcurve.h>

namespace Database {

IAggregator *ObjectFactory::createObject(int itemType)
{
    switch (itemType) {
    case Ac::ControlCurveItem:
        return (new ControlCurve)->init();
    case Ac::NoteItem:
        return (new Note)->init();
    case Ac::PitchCurveItem:
        return (new PitchCurve)->init();
    default:
        return 0;
    }
}

IAggregator *ObjectFactory::createObjectList(int itemType, int listType)
{
    switch (listType) {
    case Mi::ListItem:
        return (new ObjectList(itemType))->init();
    default:
        return 0;
    }
}

} // namespace Database
