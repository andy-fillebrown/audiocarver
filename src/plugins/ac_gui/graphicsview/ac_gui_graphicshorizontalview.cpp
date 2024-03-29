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

#include "ac_gui_graphicshorizontalview.h"
#include "ac_gui_graphicsviewmanager.h"
#include <ac_core_namespace.h>

using namespace Ac;

int GraphicsHorizontalView::horizontalPositionRole() const
{
    return TimePositionRole;
}

int GraphicsHorizontalView::horizontalScaleRole() const
{
    return TimeScaleRole;
}

qreal GraphicsHorizontalView::sceneWidth() const
{
    const GraphicsViewManager *vm = GraphicsViewManager::instance();
    return vm->scoreLength() / vm->scale(Ac::TimeScaleRole);
}
