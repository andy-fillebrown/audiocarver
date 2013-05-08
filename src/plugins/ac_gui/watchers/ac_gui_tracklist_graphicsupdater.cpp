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

#include "ac_gui_tracklist_graphicsupdater.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <QGraphicsItem>

using namespace Ac;

namespace TrackList {

GraphicsUpdater::GraphicsUpdater(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    _aggregate->appendComponent(this);
}

void *GraphicsUpdater::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

void GraphicsUpdater::endInsertItem(IModelItem *list, int index)
{
    const int child_count = list->itemCount();
    for (int i = 0;  i < child_count;  ++i) {
        IModelItem *child_item = list->itemAt(i);
        IGraphicsItem *child_graphics = query<IGraphicsItem>(child_item);
        const int z_value = child_count - i;
        child_graphics->findNode(PitchScene, MainTransform)->setZValue(z_value);
        child_graphics->findNode(ControlScene, MainTransform)->setZValue(z_value);
        child_graphics->update(VisibilityRole, child_item->getValue(VisibilityRole));
    }
}

}
