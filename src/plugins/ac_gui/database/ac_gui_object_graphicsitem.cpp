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

#include "ac_gui_object_graphicsitem.h"
#include <iaggregate.h>
#include <imodelitem.h>

namespace Object {

IGraphicsItem *GraphicsItem::parent() const
{
    IModelItem *this_item = QUERY(IModelItem, this);
    IModelItem *parent_item = this_item->parent();
    if (parent_item && parent_item->isList())
        parent_item = parent_item->parent();
    return QUERY(IGraphicsItem, parent_item);
}

}
