/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#ifndef AC_CONTROLVIEW_H
#define AC_CONTROLVIEW_H

#include <ac_graphicsview.h>

class ControlViewPrivate;

class ControlView : public GraphicsHView
{
    Q_OBJECT

public:
    ControlView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~ControlView();

protected:
    qreal sceneHeight() const;
    QPointF sceneCenter() const;

    Ac::ItemDataRole positionYRole() const { return Ac::ControlPositionRole; }
    Ac::ItemDataRole scaleYRole() const { return Ac::ControlScaleRole; }

private:
    Q_DISABLE_COPY(ControlView)
    ControlViewPrivate *d;
};

#endif // AC_CONTROLVIEW_H
