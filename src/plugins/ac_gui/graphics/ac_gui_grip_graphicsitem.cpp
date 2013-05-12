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

#include "ac_gui_grip_graphicsitem.h"
#include <igraphicsgrip.h>

namespace Grip {

int GraphicsItem::sceneType() const
{
    return parent()->sceneType();
}

void GraphicsItem::update(int role, const QVariant &value)
{
    IGraphicsGrip *grip = query<IGraphicsGrip>(this);
    if (grip)
        grip->update(role, value);
}

}
