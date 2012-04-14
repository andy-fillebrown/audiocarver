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

#include "ac_controlcurvedata.h"

#include <mi_scopeddatachange.h>

Q_IAGGREGATOR_INIT_ROLES(ControlCurveData) =
{
Ac::ControlTypeRole
};

IAggregator *ControlCurveData::init()
{
    return Base::init();
}

IAggregate *ControlCurveData::ModelData::init()
{
    return Base::init();
}

IAggregate *ControlCurveData::ModelItem::init()
{
    return Base::init();
}

bool ControlCurveData::setControlType(int controlType)
{
    if (_controlType == controlType)
        return false;
    Q_SCOPED_DATA_CHANGE((Ac::ControlTypeRole))
    _controlType = controlType;
    return true;
}
