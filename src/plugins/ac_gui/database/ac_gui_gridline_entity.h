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

#ifndef AC_GUI_GRIDLINE_ENTITY_H
#define AC_GUI_GRIDLINE_ENTITY_H

#include "ac_gui_object_entity.h"

class GraphicsItem;
class GraphicsTextItem;
class QGraphicsLineItem;

namespace GridLine {

class Entity : public Object::Entity
{
    GraphicsItem * _labelRootItem;
    GraphicsTextItem *_labelTextItem;
    QGraphicsLineItem *_labelLineItem;

protected:
    Entity(IAggregate *aggregate)
        :   Object::Entity(aggregate)
        ,   _labelRootItem(0)
        ,   _labelTextItem(0)
        ,   _labelLineItem(0)
    {}

    ~Entity();
    virtual IUnknown *initialize();

    GraphicsItem *labelRootItem() const
    {
        return _labelRootItem;
    }

    GraphicsTextItem *labelTextItem() const
    {
        return _labelTextItem;
    }

    QGraphicsLineItem *labelLineItem() const
    {
        return _labelLineItem;
    }

    void update(int role);

    void highlight()
    {}

    void unhighlight()
    {}

    bool isVisible() const;
};

}

#endif
