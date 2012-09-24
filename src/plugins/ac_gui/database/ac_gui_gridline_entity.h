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
#include <qnamespace.h>

class GraphicsItem;
class GraphicsTextItem;
class QFont;

namespace GridLine {

class Entity : public Object::Entity
{
    GraphicsItem * _labelSceneRootItem;
    GraphicsTextItem *_labelSceneTextItem;

protected:
    static const QFont &gridLabelFont();
    static Qt::PenStyle gridLinePenStyle();
    static Qt::PenStyle gridLineExtensionPenStyle();

    Entity(IAggregate *aggregate)
        :   Object::Entity(aggregate)
        ,   _labelSceneRootItem(0)
        ,   _labelSceneTextItem(0)
    {}

    ~Entity();
    virtual IUnknown *initialize();

    GraphicsItem *labelSceneRootItem() const
    {
        return _labelSceneRootItem;
    }

    GraphicsTextItem *labelSceneTextItem() const
    {
        return _labelSceneTextItem;
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
