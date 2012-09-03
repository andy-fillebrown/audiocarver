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

#ifndef AC_GUI_CURVE_ENTITY_H
#define AC_GUI_CURVE_ENTITY_H

#include "ac_gui_object_entity.h"

namespace Curve {

class Entity : public Object::Entity
{
public:
    Entity(IAggregate *aggregate)
        :   Object::Entity(aggregate)
    {}

    virtual IUnknown *initialize();

protected:
    QGraphicsItem *graphicsItem(int sceneType, int transformType) const;
    void update(int role);
    void highlight();
    void unhighlight();
    bool isVisible() const;
};

}

#endif
