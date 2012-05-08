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

#include "ac_database_objectguifactory.h"

#include <ac_database_controlcurvegui.h>
#include <ac_database_notegui.h>
#include <ac_database_pitchcurvegui.h>

namespace Database {

IAggregator *ObjectGuiFactory::createObject(int itemType)
{
    switch (itemType) {
    case Ac::ControlCurveItem:
        return (new ControlCurveGui)->init();
    case Ac::NoteItem:
        return (new NoteGui)->init();
    case Ac::PitchCurveItem:
        return (new PitchCurveGui)->init();
    default:
        return ObjectFactory::createObject(itemType);
    }
}

} // namespace Database
