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

#include "ac_coredataobjectfactory.h"

#include <ac_controlcurvedataobject.h>
#include <ac_notedataobject.h>
#include <ac_pitchcurvedataobject.h>

IAggregator *CoreDataObjectFactory::createObject(int itemType)
{
    switch (itemType) {
    case Ac::ControlCurveItem:
        return Q_NEW_DATAOBJECT(ControlCurveDataObject);
    case Ac::NoteItem:
        return Q_NEW_DATAOBJECT(NoteDataObject);
    case Ac::PitchCurveItem:
        return Q_NEW_DATAOBJECT(PitchCurveDataObject);
    default:
        return 0;
    }
}

IAggregator *CoreDataObjectFactory::createObjectList(int itemType, int listType)
{
    switch (listType) {
    case Mi::ListItem:
        return Q_NEW_DATAOBJECTLIST(DataObjectList, itemType);
    default:
        return 0;
    }
}
