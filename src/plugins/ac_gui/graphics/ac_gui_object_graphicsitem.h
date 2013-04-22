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

namespace Object {

class GraphicsItem : public Base::GraphicsItem
{
public:
    GraphicsItem(IAggregate *aggregate)
        :   Base::GraphicsItem(aggregate)
    {}

    int count() const
    {
        return 0;
    }

    IGraphicsItem *at(int i) const
    {
        return 0;
    }

    IGraphicsItem *findItem(int itemType) const
    {
        return 0;
    }

    QGraphicsItem *findNode(int sceneType, int transformType) const
    {
        return 0;
    }

    void update(int role, const QVariant &value);
};

}

#endif
