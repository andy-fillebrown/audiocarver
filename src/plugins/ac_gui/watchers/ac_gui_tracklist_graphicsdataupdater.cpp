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

#include "ac_gui_tracklist_graphicsdataupdater.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <igraphicsentitydata.h>
#include <imodelitemlist.h>
#include <QGraphicsItem>

using namespace Ac;

static void updateZValues(const IModelItemList *list)
{
    const int child_count = list->count();
    for (int i = 0;  i < child_count;  ++i) {
        const int z_value = child_count - i;
        IGraphicsEntityData *child_gdata = QUERY(IGraphicsEntityData, list->at(i));
        child_gdata->node(PitchScene, MainTransform)->setZValue(z_value);
        child_gdata->node(ControlScene, MainTransform)->setZValue(z_value);
    }
}

namespace TrackList {

GraphicsDataUpdater::GraphicsDataUpdater(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    _aggregate->append(this);
}

void *GraphicsDataUpdater::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

void GraphicsDataUpdater::endInsertItem(const IModelItemList *list, int index)
{
    updateZValues(list);
}

}
