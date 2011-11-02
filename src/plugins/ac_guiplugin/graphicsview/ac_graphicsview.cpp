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

#include <ac_model.h>

#include <mi_ieditor.h>

#include <mi_idatabase.h>
#include <mi_imodelitem.h>

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

enum ViewState {
    Zooming = 1,
    Panning
};

enum DragState {
    Picking = 1,
    DraggingGrips
};

class GraphicsViewPrivate
{
public:
    GraphicsView *q;
    QPoint dragStartPos;
    QPoint curDragPos;
    qreal zoomStartScaleX;
    qreal zoomStartScaleY;
    QPointF zoomStartPosDC;
    QPointF zoomCenterOffsetDC;
    QRect prevZoomGlyphRect;
    QPointF panStartCenter;
    QGraphicsRectItem *pickBox;
    QList<GraphicsEntityItem*> pickedEntities;
    QList<IGripItem*> gripsBeingDragged;
    QList<IEntityItem*> entitiesToUpdate;
    GraphicsRootItem *rootItem;
    quint32 viewState : 2;
    quint32 dragState : 2;
    quint32 dirty : 28;

    GraphicsViewPrivate(GraphicsView *q)
        :   q(q)
        ,   pickBox(new QGraphicsRectItem)
        ,   rootItem(new GraphicsRootItem)
        ,   viewState(0)
        ,   dragState(0)
        ,   dirty(true)
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

    QPointF startPosDC(const QPoint &pos)
    {
        return q->sceneTransform().inverted().map(QPointF(pos) + q->sceneOffset());
    }

    QPointF centerOffsetDC(const QPointF &posDC)
    {
        const ViewManager *vm = ViewManager::instance();
        return q->sceneScale().map(QPointF(vm->position(q->positionRoleX()), vm->position(q->positionRoleY())) - posDC);
    }

    void recenter(const QPointF &startPosDC, const QPointF &centerOffsetDC)
    {
        const QPointF center = startPosDC + QTransform::fromScale(q->sceneWidth() / q->width(), -q->sceneHeight() / q->height()).map(centerOffsetDC);
        ViewManager *vm = ViewManager::instance();
        vm->setPosition(center.x(), q->positionRoleX());
        vm->setPosition(center.y(), q->positionRoleY());
    }

    QRect zoomGlyphLineRect() const
    {
        return QRect(dragStartPos, curDragPos).normalized().adjusted(-1, -1, 2, 2);
    }

    QRect zoomGlyphCircleRect() const
    {
        return QRect(dragStartPos, dragStartPos).adjusted(-2, -2, 4, 4);
    }

    void startZoom(const QPoint &pos)
    {
        q->zoomStarting();
        viewState = Zooming;
        dragStartPos = curDragPos = pos;
        const ViewManager *vm = ViewManager::instance();
        zoomStartScaleX = vm->scale(q->scaleRoleX());
        zoomStartScaleY = vm->scale(q->scaleRoleY());
        zoomStartPosDC = startPosDC(pos);
        zoomCenterOffsetDC = centerOffsetDC(zoomStartPosDC);
        prevZoomGlyphRect = QRect();
        q->update(zoomGlyphCircleRect());
    }

    void zoomTo(const QPoint &pos)
    {
        curDragPos = pos;
        QPoint offset = pos - dragStartPos;
        const int x = offset.x();
        if (x) {
            qreal scale = 1.0f + (qreal(qAbs(x)) / 10.0f);
            ViewManager::instance()->setScale((x < 0 ? 1.0f / scale : scale) * zoomStartScaleX, q->scaleRoleX());
        }
        const int y = offset.y();
        if (y) {
            const qreal scale = 1.0f + qreal(qAbs(y) / 10.0f);
            ViewManager::instance()->setScale((0 < y ? 1.0f / scale : scale) * zoomStartScaleY, q->scaleRoleY());
        }
        recenter(zoomStartPosDC, zoomCenterOffsetDC);
        if (dirty)
            ViewManager::instance()->updateViews();
        else {
            const QRect rect = zoomGlyphLineRect();
            q->update(prevZoomGlyphRect.united(rect));
            prevZoomGlyphRect = rect;
        }
    }

    void finishZoom(const QPoint &pos)
    {
        zoomTo(pos);
        viewState = 0;
        q->update(QRect(dragStartPos, dragStartPos).adjusted(-2, -2, 4, 4));
        q->zoomFinished();
    }

    void startPan(const QPoint &pos)
    {
        q->panStarting();
        viewState = Panning;
        dragStartPos = pos;
        const ViewManager *vm = ViewManager::instance();
        panStartCenter.setX(vm->position(q->positionRoleX()));
        panStartCenter.setY(vm->position(q->positionRoleY()));
    }

    void panTo(const QPoint &pos)
    {
        q->setCursor(Qt::ClosedHandCursor);
        const QPointF offset = q->sceneScale().inverted().map(QPointF(pos - dragStartPos));
        const QPointF center = panStartCenter - offset;
        ViewManager *vm = ViewManager::instance();
        vm->setPosition(center.x(), q->positionRoleX());
        vm->setPosition(center.y(), q->positionRoleY());
        vm->updateViews();
    }

    void finishPan(const QPoint &pos)
    {
        panTo(pos);
        viewState = 0;
        q->panFinished();
    }

    bool selectGrips(const QPoint &pos)
    {
        const QList<QGraphicsItem*> items = q->items(pos);
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
        return !gripsBeingDragged.isEmpty();
    }

    void startDraggingGrips()
    {
        IEditor::instance()->beginCommand();
        dragState = DraggingGrips;
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->startDraggingPoints();
    }

    void dragGripsTo(const QPoint &pos)
    {
        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();
        QPointF scenePos = rootItem->transform().map(q->mapToScene(pos));
        foreach (IGripItem *grip, gripsBeingDragged)
            grip->setPosition(scenePos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->updatePoints();
        vm->enableUpdates();
    }

    void finishDraggingGrips(const QPoint &pos)
    {
        dragGripsTo(pos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->finishDraggingPoints();
        entitiesToUpdate.clear();
        gripsBeingDragged.clear();
        dragState = 0;
        IEditor::instance()->endCommand();
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
        if (QApplication::startDragDistance() <= (pos - dragStartPos).manhattanLength()) {
            const QRect pickRect = QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
            pickBox->setRect(QRectF(q->mapToScene(pickRect.topLeft()), q->mapToScene(pickRect.bottomRight())));
            pickBox->show();
        }
    }

    void finishPicking(const QPoint &pos)
    {
        bool pickOne = false;
        const QRect rect = (pickOne = (pos - dragStartPos).manhattanLength() < QApplication::startDragDistance())
                ? QRect(dragStartPos.x() - 2, dragStartPos.y() - 2, 4, 4)
                : QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
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
        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();
        foreach (IEntity *entity, entities) {
            if (entity->isVisible() && !entityIsPicked(entity)) {
                GraphicsEntityItem *item = new GraphicsEntityItem(entity);
                pickedEntities.append(item);
                item->setParentItem(rootItem);
                item->highlight();
            }
        }
        vm->enableUpdates();
    }

    void removePickedEntities(const QList<IEntity*> &entities)
    {
        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();
        foreach (IEntity *entity, entities) {
            GraphicsEntityItem *item = findEntityItem(entity);
            if (item) {
                pickedEntities.removeOne(item);
                item->unhighlight();
                delete item;
            }
        }
        vm->enableUpdates();
    }

    void clearPickedEntities()
    {
        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();
        foreach (GraphicsEntityItem *item, pickedEntities)
            item->unhighlight();
        qDeleteAll(pickedEntities);
        pickedEntities.clear();
        vm->enableUpdates();
    }

    void resetPickedEntities()
    {
        QList<IEntity*> entities;
        foreach (GraphicsEntityItem *item, pickedEntities)
            entities.append(item->entity());
        setPickedEntities(entities);
    }

    void updateViewSettings()
    {
        const qreal sceneWidth = q->sceneWidth();
        const qreal sceneHeight = q->sceneHeight();
        const qreal viewWidth = q->width();
        const qreal viewHeight = q->height();
        const QRectF sceneRect(0.0f, 0.0f, sceneWidth, sceneHeight);
        const QPointF sceneOffset = q->sceneCenter() - sceneRect.center();
        q->setSceneRect(sceneRect.translated(sceneOffset + q->sceneOffset()));
        q->setTransform(QTransform::fromScale(viewWidth / sceneWidth, viewHeight / sceneHeight));
        dirty = false;
    }
};

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new GraphicsViewPrivate(this))
{
    setInteractive(false);
    setOptimizationFlag(DontAdjustForAntialiasing);
    setOptimizationFlag(DontSavePainterState);
    setTransformationAnchor(NoAnchor);
    setViewportUpdateMode(FullViewportUpdate);
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

bool GraphicsView::isDirty() const
{
    return d->dirty;
}

void GraphicsView::updateView()
{
    if (d->dirty)
        updateViewSettings();
    update();
}

void GraphicsView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);

    // If topLeft is an entity (or subentity) and is showing grips, reset the grips.
    IModelItem *item = ViewManager::instance()->model()->itemFromIndex(topLeft);
    IEntity *entity = query<IEntity>(item);
    if (!entity) {
        ISubEntity *subEntity = query<ISubEntity>(item);
        if (subEntity)
            entity = subEntity->parentEntity();
    }
    if (entity) {
        GraphicsEntityItem *entityItem = d->findEntityItem(entity);
        if (entityItem)
            entityItem->resetGrips();
    }

    // If topLeft is a track, gripped entities might have been hidden.
    // Re-append the selected entities so the hidden ones are filtered out.
    if (Ac::TrackItem == topLeft.data(Mi::ItemTypeRole))
        d->resetPickedEntities();
}

void GraphicsView::modelAboutToBeReset()
{
    d->clearPickedEntities();
}

void GraphicsView::viewPositionChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    if (positionRoleX() == role || positionRoleY() == role)
        d->dirty = true;
}

void GraphicsView::viewScaleChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    if (scaleRoleX() == role || scaleRoleY() == role)
        d->dirty = true;
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

void GraphicsView::updateViewSettings()
{
    d->updateViewSettings();
}

void GraphicsView::paintGlyphs(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (Zooming == d->viewState) {
        QPainter painter(viewport());
        painter.drawEllipse(d->dragStartPos, 2, 2);
        painter.setPen(Qt::DotLine);
        painter.drawLine(d->dragStartPos, d->curDragPos);
    }
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    d->dirty = true;
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button()) {
        if (Picking == d->dragState)
            return;
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
    switch (d->viewState) {
    case Zooming:
        d->zoomTo(event->pos());
        break;
    case Panning:
        d->panTo(event->pos());
    }
    switch (d->dragState) {
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
        switch (d->viewState) {
        case Zooming:
            d->finishZoom(event->pos());
            break;
        case Panning:
            d->finishPan(event->pos());
        }
    } else if (Qt::LeftButton == event->button()) {
        switch (d->dragState) {
        case DraggingGrips:
            d->finishDraggingGrips(event->pos());
            break;
        case Picking:
            d->finishPicking(event->pos());
        }
    }
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (0 < d->viewState)
        return;
    const QPointF posDC = d->startPosDC(event->pos());
    const QPointF offsetDC = d->centerOffsetDC(posDC);
    const qreal scaleAmount = event->delta() < 0 ? 1.0f / 1.25f : 1.25f;
    ViewManager *vm = ViewManager::instance();
    vm->setScale(scaleAmount * vm->scale(scaleRoleX()), scaleRoleX());
    vm->setScale(scaleAmount * vm->scale(scaleRoleY()), scaleRoleY());
    d->recenter(posDC, offsetDC);
    vm->updateViews();
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (DraggingGrips == d->dragState)
        return;
    if (Qt::Key_Escape == event->key())
        d->clearPickedEntities();
}

void GraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    paintGlyphs(event);
}

qreal GraphicsHView::sceneWidth() const
{
    const ViewManager *vm = ViewManager::instance();
    return vm->scoreLength() / vm->scale(Ac::TimeScaleRole);
}
