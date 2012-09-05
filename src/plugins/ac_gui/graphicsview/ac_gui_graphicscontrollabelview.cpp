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

#include "ac_gui_graphicscontrollabelview.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>
#include <idatabase.h>
#include <imodelitem.h>

using namespace Ac;

GraphicsControlLabelView::GraphicsControlLabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsVerticalLabelView(scene, parent)
{
    setStyleSheet("QFrame {"
                  "border-top: 1px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 0px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

IModelItemList *GraphicsControlLabelView::gridLineList() const
{
    return IDatabase::instance()->rootItem()->findList(ControlGridLineItem);
}

int GraphicsControlLabelView::verticalPositionRole() const
{
    return ControlPositionRole;
}

int GraphicsControlLabelView::verticalScaleRole() const
{
    return ControlScaleRole;
}

int GraphicsControlLabelView::sceneType() const
{
    return ControlLabelScene;
}

qreal GraphicsControlLabelView::sceneHeight() const
{
    return qreal(1.0f) / GraphicsViewManager::instance()->scale(ControlScaleRole);
}
