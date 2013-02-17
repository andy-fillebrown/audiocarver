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

#include "ac_gui_object_graphicscurve.h"
#include "ac_gui_namespace.h"
#include "ac_gui_graphicsnode.h"
#include <iaggregate.h>
#include <imodelitem.h>

using namespace Ac;

namespace Object {

void *GraphicsCurve::queryInterface(int interfaceType) const
{
    if (isTypeOfInterface(interfaceType))
        return const_cast<GraphicsCurve*>(this);
    return aggregate()->queryInterface(interfaceType);
}

IUnknown *GraphicsCurve::initialize()
{
    return aggregate()->append(this);
}

IGraphicsEntity *GraphicsCurve::parent() const
{
    IModelItem *this_item = query<IModelItem>(this);
    if (!this_item)
        return 0;
    return query<IGraphicsEntity>(this_item->parent());
}

}
