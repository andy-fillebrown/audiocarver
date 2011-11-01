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

#include <ac_namespace.h>

#include <mi_graphicsview.h>

class QModelIndex;

class GraphicsViewPrivate;
class GraphicsView : public MiGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~GraphicsView();

    QTransform sceneScale() const;
    QTransform sceneTransform() const;

    bool isDirty() const;
    virtual void updateView();

public slots:
    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void modelAboutToBeReset();
    virtual void viewPositionChanged(int role);
    virtual void viewScaleChanged(int role);

protected:
    virtual qreal sceneWidth() const { return 1.0f; }
    virtual qreal sceneHeight() const { return 1.0f; }
    virtual QPointF sceneCenter() const { return QPointF(); }
    virtual QPointF sceneOffset() const { return QPointF(); }

    virtual Ac::ItemDataRole positionRoleX() const { return Ac::InvalidRole; }
    virtual Ac::ItemDataRole positionRoleY() const { return Ac::InvalidRole; }
    virtual Ac::ItemDataRole scaleRoleX() const { return Ac::InvalidRole; }
    virtual Ac::ItemDataRole scaleRoleY() const { return Ac::InvalidRole; }

    virtual void zoomStarting();
    virtual void zoomFinished();
    virtual void panStarting();
    virtual void panFinished();

    virtual void updateViewSettings();
    virtual void paintGlyphs(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *event);

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

protected:
    qreal sceneWidth() const;

    Ac::ItemDataRole positionRoleX() const { return Ac::TimePositionRole; }
    Ac::ItemDataRole scaleRoleX() const { return Ac::TimeScaleRole; }

private:
    Q_DISABLE_COPY(GraphicsHView)
};

#endif // AC_GRAPHICSVIEW_H
