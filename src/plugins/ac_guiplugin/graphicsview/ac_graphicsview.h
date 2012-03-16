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

#ifndef AC_GRAPHICSVIEW_H
#define AC_GRAPHICSVIEW_H

#include <ac_namespace.h>

#include <mi_graphicsview.h>

#include <QModelIndex>

class IGripItem;

class QItemSelection;

class GraphicsViewPrivate;
class GraphicsView : public MiGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~GraphicsView();

    static const QCursor &normalCrosshair();
    static const QCursor &creationCrosshair();

    QTransform sceneScale() const;
    QTransform sceneTransform() const;

    bool isDirty() const;
    virtual void updateView();

    void startInsertingPoints();
    void finishInsertingPoints();

    bool pointsAreSelected() const;

    void clearPickedGrips();

public slots:
    void modelAboutToBeReset();
    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight = QModelIndex());
    virtual void noteSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    virtual void viewPositionChanged(int role);
    virtual void viewScaleChanged(int role);
    virtual void scoreLengthChanged();

    void removePoints();

protected:
    virtual int sceneType() const { Q_ASSERT(false);  return -1; }

    virtual qreal sceneWidth() const { return 1.0f; }
    virtual qreal sceneHeight() const { return 1.0f; }
    virtual QPointF sceneCenter() const { return QPointF(); }
    virtual QPointF sceneOffset() const { return QPointF(); }

    virtual int positionRoleX() const { return Mi::InvalidRole; }
    virtual int positionRoleY() const { return Mi::InvalidRole; }
    virtual int scaleRoleX() const { return Mi::InvalidRole; }
    virtual int scaleRoleY() const { return Mi::InvalidRole; }

    virtual void zoomStarting();
    virtual void zoomFinished();
    virtual void panStarting();
    virtual void panFinished();

    virtual void updateViewSettings();
    virtual void paintGlyphs(QPaintEvent *event);

    bool isPlayCursorSelected() const;
    bool selectPlayCursor(const QPoint &pos);
    void dragPlayCursorTo(const QPoint &pos);
    void finishDraggingPlayCursor(const QPoint &pos);

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void leaveEvent(QEvent *event);
    bool viewportEvent(QEvent *event);

    void paintEvent(QPaintEvent *event);

private slots:
    void gripDeselected(IGripItem *grip);

private:
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

    int positionRoleX() const { return Ac::TimePositionRole; }
    int scaleRoleX() const { return Ac::TimeScaleRole; }
};

#endif // AC_GRAPHICSVIEW_H
