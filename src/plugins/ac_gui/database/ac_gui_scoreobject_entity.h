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

#ifndef AC_GUI_SCOREOBJECT_ENTITY_H
#define AC_GUI_SCOREOBJECT_ENTITY_H

#include "ac_gui_object_parententity.h"
#include <QMap>

namespace ScoreObject {

class Entity : public Object::ParentEntity
{
    QMap<int, QGraphicsItem*> _mainGraphicsItems;

public:
    Entity(IAggregate *aggregate)
        :   Object::ParentEntity(aggregate)
    {}

    virtual IUnknown *initialize();

protected:
    QMap<int, QGraphicsItem*> &mainGraphicsItems()
    {
        return _mainGraphicsItems;
    }

    QList<ISubEntity*> subEntities(int sceneType) const;
    QGraphicsItem *graphicsItem(int sceneType, int transformType) const;

    void highlight()
    {
        Q_ASSERT(false && "Not implemented yet.");
    }

    void unhighlight()
    {
        Q_ASSERT(false && "Not implemented yet.");
    }

    bool isVisible() const
    {
        Q_ASSERT(false && "Not implemented yet.");
        return false;
    }
};

}

#endif
