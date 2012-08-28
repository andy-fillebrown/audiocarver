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

#ifndef AC_GUI_TIMEGRIDLINE_ENTITY_H
#define AC_GUI_TIMEGRIDLINE_ENTITY_H

#include "ac_gui_gridline_entity.h"

namespace TimeGridLine {

class Entity : public GridLine::Entity
{
    QGraphicsLineItem *_pitchSceneLineItem;
    QGraphicsLineItem *_controlSceneLineItem;

protected:
    Entity(IAggregate *aggregate)
        :   GridLine::Entity(aggregate)
        ,   _pitchSceneLineItem(0)
        ,   _controlSceneLineItem(0)
    {}

    ~Entity();
    virtual IUnknown *initialize();

    QGraphicsLineItem *pitchSceneLineItem() const
    {
        return _pitchSceneLineItem;
    }

    QGraphicsLineItem *controlSceneLineItem() const
    {
        return _controlSceneLineItem;
    }

    QGraphicsItem *graphicsItem(int sceneType, int transformType) const;
    void update(int role);
};

}

#endif
