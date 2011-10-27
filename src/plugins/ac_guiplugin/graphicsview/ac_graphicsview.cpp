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
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/crosshair.png"));
    return cursor;
}

static const QCursor &zoomCursor()
{
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/zoom-cursor.png"));
    return cursor;
}

enum DragState {
    Zooming = 1,
    Panning,
    Picking,
    DraggingGrips
};

class GraphicsViewPrivate
{
public:
    GraphicsView *q;
    ViewManager *viewMgr;
    int dragState;
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
        ,   dragState(0)
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
        return 0 < dragState;
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
        dragState = Zooming;
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
        q->update();
    }

    void finishZoom(const QPoint &pos)
    {
        zoomTo(pos);
        dragState = 0;
        q->zoomFinished();
    }

    void startPan(const QPoint &pos)
    {
        q->panStarting();
        dragState = Panning;
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
    }

    void finishPan(const QPoint &pos)
    {
        panTo(pos);
        dragState = 0;
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
        bool draggingGrips = !gripsBeingDragged.isEmpty();
        if (draggingGrips)
            dragState = DraggingGrips;
        return draggingGrips;
    }

    void startDraggingGrips()
    {
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->startDraggingPoints();
    }

    void dragGripsTo(const QPoint &pos)
    {
        viewMgr->disableUpdates();
        QPointF scenePos = rootItem->transform().map(q->mapToScene(pos));
        foreach (IGripItem *grip, gripsBeingDragged)
            grip->setPosition(scenePos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->updatePoints();
        viewMgr->enableUpdates();
    }

    void finishDraggingGrips(const QPoint &pos)
    {
        dragGripsTo(pos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->finishDraggingPoints();
        entitiesToUpdate.clear();
        gripsBeingDragged.clear();
        dragState = 0;
    }

    QRect pickBoxBounds() const
    {
        return QRect(QPoint(), q->size()).adjusted(0, 0, -2, -1);
    }

    void startPicking(const QPoint &pos)
    {
        dragStartPos = pos;
        dragState = Picking;
    }

    void dragPickBoxTo(const QPoint &pos)
    {
        if (4 <= (pos - dragStartPos).manhattanLength()) {
            const QRect pickRect = QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
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
        const QRectF pickRect = q->sceneTransform().inverted().mapRect(QRectF(rect));
        QList<IEntity*> entities;
        const QList<QGraphicsItem*> items = q->items(rect);
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
        dragState = 0;
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
        viewMgr->disableUpdates();
        foreach (IEntity *entity, entities) {
            if (!entityIsPicked(entity)) {
                GraphicsEntityItem *item = new GraphicsEntityItem(entity);
                pickedEntities.append(item);
                item->setParentItem(rootItem);
                item->highlight();
            }
        }
        viewMgr->enableUpdates();
    }

    void removePickedEntities(const QList<IEntity*> &entities)
    {
        viewMgr->disableUpdates();
        foreach (IEntity *entity, entities) {
            GraphicsEntityItem *item = findEntityItem(entity);
            if (item) {
                pickedEntities.removeOne(item);
                item->unhighlight();
                delete item;
            }
        }
        viewMgr->enableUpdates();
    }

    void clearPickedEntities()
    {
        viewMgr->disableUpdates();
        foreach (GraphicsEntityItem *item, pickedEntities)
            item->unhighlight();
        qDeleteAll(pickedEntities);
        pickedEntities.clear();
        viewMgr->enableUpdates();
    }

    void updateViewSettings()
    {
        const qreal sceneWidth = q->sceneWidth();
        const qreal sceneHeight = q->sceneHeight();
        const qreal viewWidth = q->width();
        const qreal viewHeight = q->height();
        QRectF sceneRect(0.0f, 0.0f, sceneWidth, sceneHeight);
        const QPointF sceneOffset = q->sceneCenter() - sceneRect.center();
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
    if (d->viewMgr->databaseIsReading())
        return;
    if (positionRoleX() == role || positionRoleY() == role)
        d->updateViewSettings();
}

void GraphicsView::viewScaleChanged(int role)
{
    if (d->viewMgr->databaseIsReading())
        return;
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
    switch (d->dragState) {
    case Zooming:
        d->zoomTo(event->pos());
        break;
    case Panning:
        d->panTo(event->pos());
        break;
    case DraggingGrips:
        d->dragGripsTo(event->pos());
        break;
    case Picking:
        d->dragPickBoxTo(event->pos());
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button()) {
        switch (d->dragState) {
        case Zooming:
            d->finishZoom(event->pos());
            break;
        case Panning:
            d->finishPan(event->pos());
        default:
            break;
        }
    } else if (Qt::LeftButton == event->button()) {
        switch (d->dragState) {
        case DraggingGrips:
            d->finishDraggingGrips(event->pos());
            break;
        case Picking:
            d->finishPicking(event->pos());
        default:
            break;
        }
    }
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (Zooming == d->dragState || Panning == d->dragState)
        return;
    const qreal scaleAmount = event->delta() < 0 ? 1.0f / 1.25f : 1.25f;
    const qreal scaleX = d->viewMgr->scale(scaleRoleX());
    const qreal scaleY = d->viewMgr->scale(scaleRoleY());
    const QPointF posDC = d->startPosDC(event->pos());
    const QPointF offsetDC = d->centerOffsetDC(posDC);
    d->viewMgr->setScale(scaleAmount * scaleX, scaleRoleX());
    d->viewMgr->setScale(scaleAmount * scaleY, scaleRoleY());
    d->recenter(posDC, offsetDC);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (DraggingGrips == d->dragState)
        return;
    if (event->key() == Qt::Key_Escape)
        d->clearPickedEntities();
}

void GraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    if (Zooming == d->dragState) {
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
