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

#ifndef AC_GUI_PITCHGRIDLINE_ENTITY_H
#define AC_GUI_PITCHGRIDLINE_ENTITY_H

#include "ac_gui_horizontalgridline_entity.h"

namespace PitchGridLine {

class Entity : public HorizontalGridLine::Entity
{
public:
    Entity(IAggregate *aggregate)
        :   HorizontalGridLine::Entity(aggregate)
    {}

    virtual IUnknown *initialize();

    QGraphicsItem *graphicsItem(int sceneType, int transformType) const;
    void update(int role);
};

}

#endif
