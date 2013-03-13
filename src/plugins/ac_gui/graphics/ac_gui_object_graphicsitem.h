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

#ifndef AC_GUI_OBJECT_GRAPHICSITEM_H
#define AC_GUI_OBJECT_GRAPHICSITEM_H

#include "ac_gui_base_graphicsitem.h"
#include "ac_gui_object_graphicsitemhelper.h"

namespace Object {

class GraphicsItem : public Base::GraphicsItem
{
    GraphicsItemHelper _helper;

public:
    GraphicsItem(IAggregate *aggregate)
        :   Base::GraphicsItem(aggregate)
        ,   _helper(this)
    {}

    IGraphicsItem *parent() const
    {
        return _helper.parent();
    }
};

}

#endif
