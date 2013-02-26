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

#include "ac_gui_note_graphicsitemupdater.h"
#include <ac_core_namespace.h>
#include <mi_core_utilities.h>
#include <iaggregate.h>
#include <igraphicsdata.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <QColor>

using namespace Ac;
using namespace Mi;

namespace Note {

GraphicsItemUpdater::GraphicsItemUpdater(IAggregate *aggregate)
    :   _aggregate(aggregate)
{
    _aggregate->append(this);
}

void *GraphicsItemUpdater::queryInterface(int interfaceType) const
{
    void *i = IComponent::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

void GraphicsItemUpdater::endChangeParent(const IModelItem *child)
{
    IModelData *track_data = QUERY(IModelData, child->parent());
    QColor color = intFromColor(track_data->get<QString>(ColorRole));
    IGraphicsData *child_gdata = QUERY(IGraphicsData, child);
    if (child_gdata)
        child_gdata->update(ColorRole, color);
}

}
