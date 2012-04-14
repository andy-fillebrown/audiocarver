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

#include "ac_dataobjectfactory.h"

#include <ac_controlcurvedata.h>
#include <ac_pitchcurvedata.h>

IAggregator *DataObjectFactory::createObject(int itemType)
{
    switch (itemType) {
    case Ac::ControlCurveItem:
        return Q_NEW_DATAOBJECT(ControlCurveData);
    case Ac::PitchCurveItem:
        return Q_NEW_DATAOBJECT(PitchCurveData);
    default:
        return 0;
    }
}

IAggregator *DataObjectFactory::createObjectList(int itemType, int listType)
{
    switch (listType) {
    case Mi::ListItem:
        return Q_NEW_DATAOBJECTLIST(DataObjectList, itemType);
    default:
        return 0;
    }
}
