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

#ifndef AC_GUI_CURVE_GRAPHICSITEM_H
#define AC_GUI_CURVE_GRAPHICSITEM_H

#include "ac_gui_base_graphicsitem.h"
#include "ac_gui_object_graphicsitemhelper.h"

namespace Curve {

class GraphicsItem : public Base::GraphicsItem
{
    Object::GraphicsItemHelper _helper;
    IAggregate *_grips;

public:
    GraphicsItem(IAggregate *aggregate)
        :   Base::GraphicsItem(aggregate)
        ,   _helper(this)
        ,   _grips(0)
    {}

protected:
    ~GraphicsItem();

    IAggregate *&grips()
    {
        return _grips;
    }

    void initialize();

    IGraphicsItem *parent() const
    {
        return _helper.parent();
    }

    int count() const
    {
        return 1;
    }

    IGraphicsItem *at(int i) const;
    IGraphicsItem *findItem(int itemType) const;
};

}

#endif
