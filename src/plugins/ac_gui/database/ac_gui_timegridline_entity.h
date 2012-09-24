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

class QGraphicsLineItem;

namespace TimeGridLine {

class Entity : public GridLine::Entity
{
    QGraphicsLineItem *_labelSceneLineItem;
    QGraphicsLineItem *_pitchSceneLineItem;
    QGraphicsLineItem *_pitchSceneLineHighExtensionItem;
    QGraphicsLineItem *_pitchSceneLineLowExtensionItem;
    QGraphicsLineItem *_controlSceneLineItem;
    QGraphicsLineItem *_controlSceneLineExtensionItem;

public:
    Entity(IAggregate *aggregate)
        :   GridLine::Entity(aggregate)
        ,   _labelSceneLineItem(0)
        ,   _pitchSceneLineItem(0)
        ,   _pitchSceneLineHighExtensionItem(0)
        ,   _pitchSceneLineLowExtensionItem(0)
        ,   _controlSceneLineItem(0)
        ,   _controlSceneLineExtensionItem(0)
    {}

    ~Entity();
    virtual IUnknown *initialize();

protected:
    QGraphicsItem *graphicsItem(int sceneType, int transformType) const;
    void update(int role);
};

}

#endif
