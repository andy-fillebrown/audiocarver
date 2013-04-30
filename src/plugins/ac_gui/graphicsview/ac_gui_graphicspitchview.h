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

#ifndef AC_GUI_GRAPHICSPITCHVIEW_H
#define AC_GUI_GRAPHICSPITCHVIEW_H

#include "ac_gui_graphicshorizontalview.h"

class GraphicsPitchViewPrivate;
class GraphicsPitchView : public GraphicsHorizontalView
{
    Q_OBJECT

    GraphicsPitchViewPrivate *d;

public:
    GraphicsPitchView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~GraphicsPitchView();

public slots:
    void createNote();
    void moveNotes();

protected:
    int sceneType() const;
    int verticalPositionRole() const;
    int verticalScaleRole() const;
    qreal sceneHeight() const;
    QPointF sceneCenter() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif
