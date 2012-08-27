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

#ifndef AC_GUI_CONTROLVIEW_H
#define AC_GUI_CONTROLVIEW_H

#include "ac_gui_graphicsview.h"
#include "ac_gui_namespace.h"

class ControlViewPrivate;
class ControlView : public GraphicsHView
{
    Q_OBJECT

    ControlViewPrivate *d;

public:
    ControlView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~ControlView();

protected:
    int sceneType() const { return Ac::ControlScene; }
    qreal sceneHeight() const;
    QPointF sceneCenter() const;

    int positionRoleY() const { return Ac::ControlPositionRole; }
    int scaleRoleY() const { return Ac::ControlScaleRole; }
};

#endif
