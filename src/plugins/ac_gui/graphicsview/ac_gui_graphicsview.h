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

#ifndef AC_GUI_GRAPHICSVIEW_H
#define AC_GUI_GRAPHICSVIEW_H

#include <mi_gui_graphicsview.h>
#include <QModelIndex>

class IGraphicsGrip;
class IGraphicsItem;
class QItemSelection;

class GraphicsViewPrivate;
class GraphicsView : public Base::GraphicsView
{
    Q_OBJECT

    friend class GraphicsViewPrivate;
    GraphicsViewPrivate *d;

public:
    static const QCursor &normalCrosshair();
    static const QCursor &creationCrosshair();

    GraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~GraphicsView();

    QTransform sceneScale() const;
    QTransform sceneTransform() const;
    bool isDirty() const;
    virtual void updateView();
    void startInsertingPoints();
    void finishInsertingPoints();
    void cancelPointInsertion();
    bool pointsAreSelected() const;
    void clearPickedGrips();

    void updateSelection(const QList<IGraphicsItem*> &ss);

public slots:
    void modelAboutToBeReset();
    virtual void viewPositionChanged(int role);
    virtual void viewScaleChanged(int role);
    virtual void scoreLengthChanged();
    void removePoints();

protected:
    virtual int sceneType() const = 0;
    virtual qreal sceneWidth() const { return 1.0f; }
    virtual qreal sceneHeight() const { return 1.0f; }
    virtual QPointF sceneCenter() const { return QPointF(); }
    virtual QPointF sceneOffset() const { return QPointF(); }
    virtual int horizontalPositionRole() const;
    virtual int verticalPositionRole() const;
    virtual int horizontalScaleRole() const;
    virtual int verticalScaleRole() const;
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
    void clearGripSelection();
    void gripDeselected(IGraphicsGrip *grip);
};

#endif
