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

#ifndef AC_GRAPHICSVIEW_H
#define AC_GRAPHICSVIEW_H

#include <mi_graphicsview.h>

class GraphicsViewPrivate;

class GraphicsView : public MiGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~GraphicsView();

protected:
    void resizeEvent(QResizeEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    virtual qreal sceneHeight() const { return 1.0f; }

private:
    Q_DISABLE_COPY(GraphicsView)
    GraphicsViewPrivate *d;
    friend class GraphicsViewPrivate;

    friend class GraphicsHView;
};

class GraphicsHView : public GraphicsView
{
    Q_OBJECT

public:
    GraphicsHView(QGraphicsScene *scene = 0, QWidget *parent = 0)
        :   GraphicsView(scene, parent)
    {}

public slots:
    void scoreDataChanged();

private:
    Q_DISABLE_COPY(GraphicsHView)
};

#endif // AC_GRAPHICSVIEW_H
