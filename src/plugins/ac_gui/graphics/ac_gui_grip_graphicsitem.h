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

#ifndef AC_GUI_GRIP_GRAPHICSITEM_H
#define AC_GUI_GRIP_GRAPHICSITEM_H

#include <ac_gui_object_graphicsitem.h>

class GraphicsGripItem;

namespace Grip {

class GraphicsItem : public Object::GraphicsItem
{
    GraphicsGripItem *_graphicsGripItem;

public:
    GraphicsItem(IAggregate *aggregate)
        :   Object::GraphicsItem(aggregate)
        ,   _graphicsGripItem(0)
    {}

    ~GraphicsItem();
    IUnknown *initialize();

    GraphicsGripItem *graphicsGripItem() const
    {
        return _graphicsGripItem;
    }

    void setColor(int color);
    void setPoints(const PointList &points);
    bool intersects(const QRectF &rect) const;
    void highlight(bool on);
    bool isVisible() const;
};

#endif
