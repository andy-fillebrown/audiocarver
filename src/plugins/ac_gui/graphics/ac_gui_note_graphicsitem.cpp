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

#include "ac_gui_note_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <imodelitem.h>

using namespace Ac;

namespace Note {

QList<IGraphicsItem*> GraphicsItem::subentities(int sceneType, int transformType) const
{
    QList<IGraphicsItem*> subents = ScoreObject::GraphicsItem::subentities(sceneType, transformType);
    IModelItem *this_item = QUERY(IModelItem, this);
    IModelItem *velocity_item = this_item->findItem(VelocityItem);
    IGraphicsItem *velocity_gitem = QUERY(IGraphicsItem, velocity_item);
    if (velocity_gitem)
        subents.append(velocity_gitem);
    return subents;
}

}
