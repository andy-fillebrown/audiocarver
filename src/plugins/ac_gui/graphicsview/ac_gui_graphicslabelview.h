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

#ifndef AC_GUI_GRAPHICSLABELVIEW_H
#define AC_GUI_GRAPHICSLABELVIEW_H

#include "ac_gui_graphicsview.h"

class IModelItem;
class QModelIndex;

class GraphicsLabelView : public GraphicsView
{
    uint _updatesDisabled : 1;

public:
    void updateView();

protected:
    GraphicsLabelView(QGraphicsScene *scene = 0, QWidget *parent = 0);

    void updateGridLineVisibilities();
    void viewScaleChanged(int role);
    void scoreLengthChanged();
    void dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft);
    virtual qreal paddingScale() const = 0;
    virtual IModelItem *gridLineList() const = 0;
    virtual int scaleRole() const = 0;

    QPointF sceneOffset() const
    {
        return QPointF(0.0f, qreal(10.0f) / (qreal(height()) / sceneHeight()));
    }

    void panFinished();
    void zoomFinished();
    void updateViewSettings();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif
