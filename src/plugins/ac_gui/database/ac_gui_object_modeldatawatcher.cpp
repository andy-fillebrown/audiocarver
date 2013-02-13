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

#include "ac_gui_object_modeldatawatcher.h"
#include "ac_gui_namespace.h"
#include <iaggregate.h>
#include <igraphicsitem.h>
#include <imodeldata.h>

using namespace Ac;

namespace Object {

IUnknown *ModelDataWatcher::initialize()
{
    return aggregate()->append(this);
}

void *ModelDataWatcher::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<ModelDataWatcher*>(this);
    return aggregate()->queryInterface(interfaceType);
}

void ModelDataWatcher::beginChangeData(const IModelData *data, int role, int changeType)
{}

void ModelDataWatcher::endChangeData(const IModelData *data, int role, int changeType)
{
    IGraphicsItem *graphics_item = query<IGraphicsItem>(data);
    if (!graphics_item)
        return;
    graphics_item->update(role);
}

}
