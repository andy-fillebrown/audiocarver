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

#include "ac_gui_graphicsverticallabelview.h"
#include "ac_gui_graphicsviewmanager.h"

static const QCursor &zoomCursor()
{
    static const QCursor cursor(QPixmap(":/ac_gui/images/zoom-v-cursor.png"));
    return cursor;
}

QPointF GraphicsVerticalLabelView::sceneCenter() const
{
    return QPointF(qreal(0.5f), -GraphicsViewManager::instance()->position(verticalPositionRole()));
}

void GraphicsVerticalLabelView::zoomStarting()
{
    setCursor(zoomCursor());
}
