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
#include <igraphicsentityitem.h>
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
        IGraphicsEntityItem *gitem = QUERY(IGraphicsEntityItem, this);
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            QList<IGraphicsItem*> subents = gitem->subentities(i, MainTransform);
            foreach (IGraphicsItem *subent_gitem, subents) {
                IGraphicsData *subent_gdata = QUERY(IGraphicsData, subent_gitem);
                subent_gdata->update(role, value);
            }
        }
    }
}

}
