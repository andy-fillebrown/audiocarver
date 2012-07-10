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

#include "ac_database_controlcurve.h"

#include <mi_scopeddatachange.h>

namespace Core {

IAggregator *ControlCurve::init()
{
    return Curve::init();
}

IAggregate *ControlCurve::ModelData::init()
{
    return Curve::ModelData::init();
}

IAggregate *ControlCurve::ModelItem::init()
{
    return Curve::ModelItem::init();
}

bool ControlCurve::setControlType(int controlType)
{
    if (_controlType == controlType)
        return false;
    ScopedDataChange data_change(this, Ac::ControlTypeRole);
    _controlType = controlType;
    return true;
}

} // namespace Core
