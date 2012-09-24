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

#ifndef AC_GUI_GRAPHICSVERTICALLABELVIEW_H
#define AC_GUI_GRAPHICSVERTICALLABELVIEW_H

#include "ac_gui_graphicslabelview.h"

class GraphicsVerticalLabelView : public GraphicsLabelView
{
protected:
    GraphicsVerticalLabelView(QGraphicsScene *scene = 0, QWidget *parent = 0)
        :   GraphicsLabelView(scene, parent)
    {}

    qreal paddingScale() const
    {
        return -sceneTransform().m22();
    }

    int scaleRole() const
    {
        return verticalScaleRole();
    }

    QPointF sceneOffset() const
    {
        return QPointF(qreal(-2.0f) / (qreal(width()) / sceneWidth()), qreal(8.5f) / (qreal(height()) / sceneHeight()));
    }

    QPointF sceneCenter() const;
    void zoomStarting();
};

#endif
