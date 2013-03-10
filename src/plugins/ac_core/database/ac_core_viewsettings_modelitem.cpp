/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_core_viewsettings_modelitem.h"
#include "ac_core_constants.h"
#include "ac_core_namespace.h"
#include <imodeldata.h>

using namespace Ac;

namespace ViewSettings {

void ModelItem::reset()
{
    IModelData *data = QUERY(IModelData, this);
    data->set(DEFAULT_VIEWSETTINGS_TIMEPOSITION, TimePositionRole);
    data->set(DEFAULT_VIEWSETTINGS_PITCHPOSITION, PitchPositionRole);
    data->set(DEFAULT_VIEWSETTINGS_CONTROLPOSITION, ControlPositionRole);
    data->set(VIEWSCALE_MIN, TimeScaleRole);
    data->set(VIEWSCALE_MIN, PitchScaleRole);
    data->set(VIEWSCALE_MIN, ControlScaleRole);
    Object::ModelItem::reset();
}

}
