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

#include "ac_gui_object_graphicsitem.h"
#include <igraphicsgrip.h>
#include <igraphicsgriplist.h>

namespace Object {

void GraphicsItem::update(int role, const QVariant &value)
{
    IGraphicsGripList *grip_list = query<IGraphicsGripList>(this);
    if (grip_list)
        grip_list->update(role, value);
    IGraphicsGrip *grip = query<IGraphicsGrip>(this);
    if (grip)
        grip->update(role, value);
}

}
