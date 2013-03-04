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

#include "ac_gui_graphicscontrolview.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>

using namespace Ac;

GraphicsControlView::GraphicsControlView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsHorizontalView(scene, parent)
{
    setStyleSheet("QFrame {"
                  "border-top: 1px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 1px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

int GraphicsControlView::sceneType() const
{
    return ControlScene;
}

int GraphicsControlView::verticalPositionRole() const
{
    return ControlPositionRole;
}

int GraphicsControlView::verticalScaleRole() const
{
    return ControlScaleRole;
}

qreal GraphicsControlView::sceneHeight() const
{
    return qreal(1.0f) / GraphicsViewManager::instance()->scale(Ac::ControlScaleRole);
}

QPointF GraphicsControlView::sceneCenter() const
{
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    return QPointF(vm->position(TimePositionRole), -vm->position(ControlPositionRole));
}
