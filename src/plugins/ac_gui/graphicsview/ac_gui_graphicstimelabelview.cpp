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

#include "ac_gui_graphicstimelabelview.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>
#include <idatabase.h>
#include <imodelitem.h>

using namespace Ac;

static const QCursor &zoomCursor()
{
    static QCursor cursor(QPixmap(":/ac_gui/images/zoom-h-cursor.png"));
    return cursor;
}

GraphicsTimeLabelView::GraphicsTimeLabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsLabelView(scene, parent)
{
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 1px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

IModelItem *GraphicsTimeLabelView::gridLineList() const
{
    return IDatabase::instance()->rootItem()->findItem(TimeGridLineListItem);
}

int GraphicsTimeLabelView::scaleRole() const
{
    return TimeScaleRole;
}

int GraphicsTimeLabelView::sceneType() const
{
    return TimeLabelScene;
}

int GraphicsTimeLabelView::horizontalPositionRole() const
{
    return TimePositionRole;
}

int GraphicsTimeLabelView::horizontalScaleRole() const
{
    return TimeScaleRole;
}

qreal GraphicsTimeLabelView::sceneWidth() const
{
    const GraphicsViewManager *vm = GraphicsViewManager::instance();
    return vm->scoreLength() / vm->scale(TimeScaleRole);
}

QPointF GraphicsTimeLabelView::sceneCenter() const
{
    const GraphicsViewManager *vm = GraphicsViewManager::instance();
    return QPointF(vm->position(TimePositionRole), qreal(0.0f));
}

void GraphicsTimeLabelView::zoomStarting()
{
    setCursor(zoomCursor());
}
