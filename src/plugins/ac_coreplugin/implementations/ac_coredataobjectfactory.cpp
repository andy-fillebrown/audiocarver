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

#include <ac_controlcurve.h>
#include <ac_pitchcurve.h>

IAggregator *CoreDataObjectFactory::createDataObject(int itemType)
{
    switch (itemType) {
    case Ac::ControlCurveItem:
        return Q_I_NEW__DATA_OBJECT(ControlCurve);
    case Ac::PitchCurveItem:
        return Q_I_NEW__DATA_OBJECT(PitchCurve);
    default:
        return 0;
    }
}

IAggregator *CoreDataObjectFactory::createDataObjectList(int itemType, int listType)
{
    switch (listType) {
    case Mi::ListItem:
        return Q_I_NEW__DATA_OBJECT_LIST(DataObjectList, itemType);
    default:
        return 0;
    }
}
