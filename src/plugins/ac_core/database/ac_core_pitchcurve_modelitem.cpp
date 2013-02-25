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

#include "ac_core_pitchcurve_modelitem.h"
#include "ac_core_namespace.h"

using namespace Ac;

namespace PitchCurve {

int ModelItem::itemType() const
{
    return PitchCurveItem;
}

bool ModelItem::isTypeOfItem(int itemType) const
{
    if (PitchCurveItem == itemType)
        return true;
    return Curve::ModelItem::isTypeOfItem(itemType);
}

}
