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

#include "ac_graphicsview.h"

#include <ac_graphicsentityitem.h>
#include <ac_graphicsgripitem.h>
#include <ac_ientity.h>
#include <ac_viewmanager.h>

#include <QApplication>
#include <QMouseEvent>

#include <qmath.h>

static const QCursor &crosshair()
{
    static QCursor cursor(QPixmap(":/ac_guiplugin/images/crosshair.png"));
    return cursor;
}

static const QCursor &zoomCursor()
{
    static QCursor cursor(QPixmap(":/ac_guiplugin/images/zoom-cursor.png"));
    return cursor;
}

class GraphicsViewPrivate
{
public:
    GraphicsView *q;
    ViewManager *viewMgr;
    int zooming : 1;
    int panning : 1;
    int picking : 1;
    int draggingGrips : 29;
    QPoint dragStartPos;
    QPoint curDragPos;
    qreal zoomStartScaleX;
    qreal zoomStartScaleY;
    QPointF zoomStartPosDC;
    QPointF zoomCenterOffsetDC;
    QPointF panStartCenter;
    QGraphicsRectItem *pickBox;
    QList<GraphicsEntityItem*> pickedEntities;
    QList<IGripItem*> gripsBeingDragged;
    QList<IEntityItem*> entitiesToUpdate;
    GraphicsRootItem *rootItem;

    GraphicsViewPrivate(GraphicsView *q)
        :   q(q)
        ,   viewMgr(ViewManager::instance())
        ,   zooming(false)
        ,   panning(false)
        ,   picking(false)
        ,   draggingGrips(false)
        ,   pickBox(new QGraphicsRectItem)
        ,   rootItem(new GraphicsRootItem)
    {
        QGraphicsScene *scene = q->scene();
        scene->addItem(rootItem);
        rootItem->setZValue(Q_FLOAT_MAX - 1.0f);
        scene->addItem(pickBox);
        pickBox->setZValue(Q_FLOAT_MAX);
        pickBox->setPen(QPen(QColor(0, 0, 255)));
        pickBox->setBrush(QBrush(QColor(0, 0, 255, 63)));
        pickBox->hide();
    }

    virtual ~GraphicsViewPrivate()
    {}

    bool isDragging() const
    {
        return panning || picking || zooming || draggingGrips;
    }

    QPointF startPosDC(const QPoint &pos)
    {
        return q->sceneTransform().inverted().map(QPointF(pos) + q->sceneOffset());
    }

    QPointF centerOffsetDC(const QPointF &posDC)
    {
        QPointF center = QPointF(viewMgr->position(q->positionRoleX()), viewMgr->position(q->positionRoleY()));
        return q->sceneScale().map(center - posDC);
    }

    void recenter(const QPointF &startPosDC, const QPointF &centerOffsetDC)
    {
        QPointF center = startPosDC + QTransform::fromScale(q->sceneWidth() / q->width(), -q->sceneHeight() / q->height()).map(centerOffsetDC);
        viewMgr->setPosition(center.x(), q->positionRoleX());
        viewMgr->setPosition(center.y(), q->positionRoleY());
    }

    void startZoom(const QPoint &pos)
    {
        q->zoomStarting();
        zooming = true;
        dragStartPos = curDragPos = pos;
        zoomStartScaleX = viewMgr->scale(q->scaleRoleX());
        zoomStartScaleY = viewMgr->scale(q->scaleRoleY());
        zoomStartPosDC = startPosDC(pos);
        zoomCenterOffsetDC = centerOffsetDC(zoomStartPosDC);
    }

    void zoomTo(const QPoint &pos)
    {
        curDragPos = pos;
        QPoint offset = pos - dragStartPos;
        if (offset.x()) {
            qreal x = offset.x();
            qreal scale = 1.0f + (qAbs(x) / 10.0f);
            if (x < 0.0f)
                scale = 1.0f / scale;
            viewMgr->setScale(scale * zoomStartScaleX, q->scaleRoleX());
        }
        if (offset.x()) {
            qreal y = offset.y();
            qreal scale = 1.0f + (qAbs(y) / 10.0f);
            if (0.0f < y)
                scale = 1.0f / scale;
            viewMgr->setScale(scale * zoomStartScaleY, q->scaleRoleY());
        }
        recenter(zoomStartPosDC, zoomCenterOffsetDC);
        viewMgr->updateViews();
    }

    void finishZoom(const QPoint &pos)
    {
        zoomTo(pos);
        zooming = false;
        q->zoomFinished();
    }

    void startPan(const QPoint &pos)
    {
        q->panStarting();
        panning = true;
        dragStartPos = pos;
        panStartCenter.setX(viewMgr->position(q->positionRoleX()));
        panStartCenter.setY(viewMgr->position(q->positionRoleY()));
    }

    void panTo(const QPoint &pos)
    {
        q->setCursor(Qt::ClosedHandCursor);
        QPointF offset = q->sceneScale().inverted().map(QPointF(pos - dragStartPos));
        QPointF center = panStartCenter - offset;
        viewMgr->setPosition(center.x(), q->positionRoleX());
        viewMgr->setPosition(center.y(), q->positionRoleY());
        viewMgr->updateViews();
    }

    void finishPan(const QPoint &pos)
    {
        panTo(pos);
        panning = false;
        q->panFinished();
    }

    bool selectGrips(const QPoint &pos)
    {
        QList<QGraphicsItem*> items = q->items(pos);
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = Q_U(item);
            if (unknown) {
                IGripItem *grip = query<IGripItem>(unknown);
                if (grip && !gripsBeingDragged.contains(grip)) {
                    gripsBeingDragged.append(grip);
                    IEntityItem *entity = grip->parentEntityItem();
                    if (!entitiesToUpdate.contains(entity))
                        entitiesToUpdate.append(entity);
                }
            }
        }
        draggingGrips = !gripsBeingDragged.isEmpty();
        return draggingGrips;
    }

    void startDraggingGrips()
    {
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->startDraggingPoints();
    }

    void dragGripsTo(const QPoint &pos)
    {
        viewMgr->setUpdatesEnabled(false);
        QPointF scenePos = rootItem->transform().map(q->mapToScene(pos));
        foreach (IGripItem *grip, gripsBeingDragged)
            grip->setPosition(scenePos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->updatePoints();
        viewMgr->setUpdatesEnabled(true);
    }

    void finishDraggingGrips(const QPoint &pos)
    {
        dragGripsTo(pos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->finishDraggingPoints();
        entitiesToUpdate.clear();
        gripsBeingDragged.clear();
        draggingGrips = false;
    }

    QRect pickBoxBounds() const
    {
        return QRect(QPoint(), q->size()).adjusted(0, 0, -2, -1);
    }

    void startPicking(const QPoint &pos)
    {
        dragStartPos = pos;
        picking = true;
    }

    void dragPickBoxTo(const QPoint &pos)
    {
        if (4 <= (pos - dragStartPos).manhattanLength()) {
            QRect pickRect = QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
            pickBox->setRect(QRectF(q->mapToScene(pickRect.topLeft()), q->mapToScene(pickRect.bottomRight())));
            pickBox->show();
        }
    }

    void finishPicking(const QPoint &pos)
    {
        bool pickOne = false;
        QRect rect;
        if ((pickOne = (pos - dragStartPos).manhattanLength() < 4))
            rect = QRect(dragStartPos.x() - 2, dragStartPos.y() - 2, 4, 4);
        else
            rect = QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
        QRectF pickRect = q->sceneTransform().inverted().mapRect(QRectF(rect));
        QList<IEntity*> entities;
        QList<QGraphicsItem*> items = q->items(rect);
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = Q_U(item);
            if (unknown) {
                IEntity *entity = query<IEntity>(unknown);
                if (entity && entity->intersects(pickRect)) {
                    entities.append(entity);
                    if (pickOne)
                        break;
                }
            }
        }
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            appendPickedEntities(entities);
        else if (QApplication::keyboardModifiers() & Qt::ControlModifier)
            removePickedEntities(entities);
        else
            setPickedEntities(entities);
        pickBox->hide();
        picking = false;
    }

    bool entityIsPicked(IEntity *entity)
    {
        foreach (GraphicsEntityItem *item, pickedEntities)
            if (item->entity() == entity)
                return true;
        return false;
    }

    GraphicsEntityItem *findEntityItem(IEntity *entity)
    {
        foreach (GraphicsEntityItem *item, pickedEntities)
            if (item->entity() == entity)
                return item;
        return 0;
    }

    void setPickedEntities(const QList<IEntity*> &entities)
    {
        clearPickedEntities();
        appendPickedEntities(entities);
    }

    void appendPickedEntities(const QList<IEntity*> &entities)
    {
        viewMgr->setUpdatesEnabled(false);
        foreach (IEntity *entity, entities) {
            if (!entityIsPicked(entity)) {
                GraphicsEntityItem *item = new GraphicsEntityItem(entity);
                pickedEntities.append(item);
                item->setParentItem(rootItem);
                item->highlight();
            }
        }
        viewMgr->setUpdatesEnabled(true);
    }

    void removePickedEntities(const QList<IEntity*> &entities)
    {
        viewMgr->setUpdatesEnabled(false);
        foreach (IEntity *entity, entities) {
            GraphicsEntityItem *item = findEntityItem(entity);
            if (item) {
                pickedEntities.removeOne(item);
                item->unhighlight();
                delete item;
            }
        }
        viewMgr->setUpdatesEnabled(true);
    }

    void clearPickedEntities()
    {
        viewMgr->setUpdatesEnabled(false);
        foreach (GraphicsEntityItem *item, pickedEntities)
            item->unhighlight();
        qDeleteAll(pickedEntities);
        pickedEntities.clear();
        viewMgr->setUpdatesEnabled(true);
    }

    void updateViewSettings()
    {
        qreal sceneWidth = q->sceneWidth();
        qreal sceneHeight = q->sceneHeight();
        qreal viewWidth = q->width();
        qreal viewHeight = q->height();
        QRectF sceneRect(0.0f, 0.0f, sceneWidth, sceneHeight);
        QPointF sceneOffset = q->sceneCenter() - sceneRect.center();
        sceneRect.translate(sceneOffset + q->sceneOffset());
        q->setSceneRect(sceneRect);
        q->setTransform(QTransform::fromScale(viewWidth / sceneWidth, viewHeight / sceneHeight));
    }
};

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new GraphicsViewPrivate(this))
{
    setInteractive(false);
    setOptimizationFlag(DontSavePainterState);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(crosshair());
}

GraphicsView::~GraphicsView()
{
    delete d;
}

QTransform GraphicsView::sceneScale() const
{
    QTransform xform = sceneTransform();
    return QTransform::fromScale(xform.m11(), xform.m22());
}

QTransform GraphicsView::sceneTransform() const
{
    return d->rootItem->transform() * viewportTransform();
}

void GraphicsView::modelAboutToBeReset()
{
    d->clearPickedEntities();
}

void GraphicsView::viewPositionChanged(int role)
{
    if (positionRoleX() == role || positionRoleY() == role)
        d->updateViewSettings();
}

void GraphicsView::viewScaleChanged(int role)
{
    if (scaleRoleX() == role || scaleRoleY() == role)
        d->updateViewSettings();
}

void GraphicsView::zoomStarting()
{
    setCursor(zoomCursor());
}

void GraphicsView::zoomFinished()
{
    setCursor(crosshair());
}

void GraphicsView::panStarting()
{
    setCursor(Qt::ClosedHandCursor);
}

void GraphicsView::panFinished()
{
    setCursor(crosshair());
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    d->updateViewSettings();
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (d->isDragging())
        return;
    if (Qt::RightButton == event->button()) {
        if (event->modifiers() & Qt::ControlModifier)
            d->startZoom(event->pos());
        else
            d->startPan(event->pos());
    } else if (Qt::LeftButton == event->button()) {
        if (d->selectGrips(event->pos()))
            d->startDraggingGrips();
        else
            d->startPicking(event->pos());
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->zooming)
        d->zoomTo(event->pos());
    else if (d->panning)
        d->panTo(event->pos());
    else if (d->draggingGrips)
        d->dragGripsTo(event->pos());
    else if (d->picking)
        d->dragPickBoxTo(event->pos());
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button()) {
        if (d->zooming)
            d->finishZoom(event->pos());
        else if (d->panning)
            d->finishPan(event->pos());
    } else if (Qt::LeftButton == event->button()) {
        if (d->draggingGrips)
            d->finishDraggingGrips(event->pos());
        else if (d->picking)
            d->finishPicking(event->pos());
    }
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (d->zooming || d->panning)
        return;
    qreal scaleAmount = 1.25f;
    if (event->delta() < 0)
        scaleAmount = 1.0f / scaleAmount;
    qreal scaleX = scaleAmount * d->viewMgr->scale(scaleRoleX());
    qreal scaleY = scaleAmount * d->viewMgr->scale(scaleRoleY());
    QPointF posDC = d->startPosDC(event->pos());
    QPointF offsetDC = d->centerOffsetDC(posDC);
    d->viewMgr->setScale(scaleX, scaleRoleX());
    d->viewMgr->setScale(scaleY, scaleRoleY());
    d->recenter(posDC, offsetDC);
    d->viewMgr->updateViews();
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (d->draggingGrips)
        return;
    if (event->key() == Qt::Key_Escape)
        d->clearPickedEntities();
}

void GraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    if (d->zooming) {
        QPainter painter(viewport());
        painter.drawEllipse(d->dragStartPos, 2, 2);
        painter.setPen(Qt::DotLine);
        painter.drawLine(d->dragStartPos, d->curDragPos);
    }
}

qreal GraphicsHView::sceneWidth() const
{
    return d->viewMgr->scoreLength() / d->viewMgr->scale(Ac::TimeScaleRole);
}
