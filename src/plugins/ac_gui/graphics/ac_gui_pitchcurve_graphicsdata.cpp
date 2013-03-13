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

#include "ac_gui_pitchcurve_graphicsdata.h"
#include "ac_gui_namespace.h"
#include <igraphicsitem.h>
#include <imodeldata.h>

using namespace Ac;

namespace PitchCurve {

void GraphicsData::update(int role, const QVariant &value)
{
    if (PointsRole == role) {
        IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
        IModelData *note_data = QUERY(IModelData, this_gitem->parent());
        IGraphicsData *note_gdata = QUERY(IGraphicsData, note_data);
        note_gdata->update(VolumeRole, note_data->getValue(VolumeRole));
    }
    Curve::GraphicsData::update(role, value);
}

}
