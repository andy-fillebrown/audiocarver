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

#include "ac_gui_note_graphicsupdater.h"
#include <ac_core_namespace.h>
#include <mi_core_utilities.h>
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <QColor>

using namespace Ac;
using namespace Mi;

namespace Note {

void GraphicsUpdater::endChangeParent(const IModelItem *child)
{
    IGraphicsItem *child_graphics = query<IGraphicsItem>(child);
    IModelItem *track_item = query<IModelItem>(child_graphics->parent());
    if (track_item) {
        QColor color = intFromColor(get<QString>(track_item, ColorRole));
        child_graphics->update(ColorRole, color);
    }
    Object::GraphicsUpdater::endChangeParent(child);
}

}
