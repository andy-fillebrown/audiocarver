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

#include "ac_gui_object_graphicsitemhelper.h"
#include <igraphicsitem.h>
#include <imodelitem.h>

namespace Object {

IGraphicsItem *GraphicsItemHelper::parent() const
{
    IModelItem *item = QUERY(IModelItem, _gitem);
    IModelItem *parent_item = item->parent();
    if (parent_item && parent_item->isList())
        parent_item = parent_item->parent();
    return QUERY(IGraphicsItem, parent_item);
}

}
