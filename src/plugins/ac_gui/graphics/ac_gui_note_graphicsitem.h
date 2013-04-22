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

#ifndef AC_GUI_NOTE_GRAPHICSITEM_H
#define AC_GUI_NOTE_GRAPHICSITEM_H

#include "ac_gui_scoreobject_graphicsitem.h"

namespace Note {

class GraphicsItem : public ScoreObject::GraphicsItem
{
    IAggregate *_velocity;

public:
    GraphicsItem(IAggregate *aggregate)
        :   ScoreObject::GraphicsItem(aggregate)
        ,   _velocity(0)
    {}

protected:
    ~GraphicsItem();

    void initialize();

    int itemCount() const
    {
        return ScoreObject::GraphicsItem::itemCount() + 1;
    }

    IGraphicsItem *itemAt(int i) const;
    IGraphicsItem *findItem(int itemType) const;
    void update(int role, const QVariant &value);
};

}

#endif
