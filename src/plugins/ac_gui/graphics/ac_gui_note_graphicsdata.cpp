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

#include "ac_gui_note_graphicsdata.h"
#include "ac_gui_namespace.h"
#include <idatabaseobjectfactory.h>
#include <igraphicsitem.h>
#include <imodeldata.h>
#include <imodelitemlist.h>
#include <mi_core_utilities.h>

using namespace Ac;
using namespace Mi;

namespace Note {

void GraphicsData::update(int role, const QVariant &value)
{
    if (ColorRole == role
            || VolumeRole == role
            || HighlightRole == role) {
        IGraphicsItem *this_gitem = QUERY(IGraphicsItem, this);
        QUERY(IGraphicsData, this_gitem->findItem(PitchCurveItem))->update(role, value);
        QUERY(IGraphicsData, this_gitem->findItem(VelocityItem))->update(role, value);
    }
}

}
