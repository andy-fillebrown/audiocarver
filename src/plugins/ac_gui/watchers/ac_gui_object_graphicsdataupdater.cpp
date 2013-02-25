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

#include "ac_gui_object_graphicsdataupdater.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <igraphicsdata.h>
#include <imodeldata.h>

using namespace Ac;

namespace Object {

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

void GraphicsDataUpdater::endChangeData(const IModelData *data, int role, int changeType)
{
    IGraphicsData *gdata = query<IGraphicsData>(data);
    if (gdata)
        gdata->update(role);
}

}
