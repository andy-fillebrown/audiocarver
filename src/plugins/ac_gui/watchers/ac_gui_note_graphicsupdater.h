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

#ifndef AC_GUI_NOTE_GRAPHICSUPDATER_H
#define AC_GUI_NOTE_GRAPHICSUPDATER_H

#include <ac_gui_object_graphicsupdater.h>

class IAggregate;

namespace Note {

class GraphicsUpdater : public Object::GraphicsUpdater
{
public:
    GraphicsUpdater(IAggregate *aggregate)
        :   Object::GraphicsUpdater(aggregate)
    {}

protected:
    void endChangeParent(IModelItem *child);
};

}

#endif
