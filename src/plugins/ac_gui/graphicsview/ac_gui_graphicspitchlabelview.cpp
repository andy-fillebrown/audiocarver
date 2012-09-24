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

#include "ac_gui_graphicspitchlabelview.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>
#include <idatabase.h>
#include <imodel.h>
#include <imodelitemlist.h>

using namespace Ac;

GraphicsPitchLabelView::GraphicsPitchLabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsVerticalLabelView(scene, parent)
{
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 0px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

IModelItemList *GraphicsPitchLabelView::gridLineList() const
{
    return IDatabase::instance()->rootItem()->findList(PitchGridLineItem);
}

int GraphicsPitchLabelView::sceneType() const
{
    return PitchLabelScene;
}

int GraphicsPitchLabelView::verticalPositionRole() const
{
    return PitchPositionRole;
}

int GraphicsPitchLabelView::verticalScaleRole() const
{
    return PitchScaleRole;
}

qreal GraphicsPitchLabelView::sceneHeight() const
{
    return qreal(127.0f) / GraphicsViewManager::instance()->scale(PitchScaleRole);
}
