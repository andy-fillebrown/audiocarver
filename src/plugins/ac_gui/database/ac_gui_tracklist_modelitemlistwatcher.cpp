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

#include "ac_gui_tracklist_modelitemlistwatcher.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <ientity.h>
#include <imodelitemlist.h>
#include <QGraphicsItem>

using namespace Ac;

namespace TrackList {

IUnknown *ModelItemListWatcher::initialize()
{
    return aggregate()->append(this);
}

void *ModelItemListWatcher::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelItemListWatcher*>(this);
    return aggregate()->queryInterface(interfaceType);
}

void ModelItemListWatcher::updateZValues(const IModelItemList *parent)
{
    const int item_count = parent->count();
    for (int i = 0;  i < item_count;  ++i) {
        const int z_value = item_count - i;
        IEntity *item_entity = query<IEntity>(parent->at(i));
        item_entity->graphicsItem(PitchScene, MainTransform)->setZValue(z_value);
        item_entity->graphicsItem(ControlScene, MainTransform)->setZValue(z_value);
    }
}

void ModelItemListWatcher::endInsertItem(const IModelItemList *parent, int index)
{
    updateZValues(parent);
}

void ModelItemListWatcher::endRemoveItem(const IModelItemList *parent, int index)
{
    updateZValues(parent);
}

}
