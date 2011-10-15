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
#include <ac_graphicsscene.h>
#include <ac_viewmanager.h>

#include <ac_ientity.h>
#include <ac_model.h>

#include <QApplication>
#include <QBitmap>
#include <QGraphicsItem>
#include <QMouseEvent>

#include <qmath.h>

class GraphicsViewPrivate
{
public:
    GraphicsView *q;
    bool panning;
    QPoint panStartPos;
    QPointF panStartCenter;
    bool dragging;
    bool draggingGrips;
    QPoint dragOrigin;
    QList<GraphicsEntityItem*> selectedEntities;
    QList<IEntityItem*> entitiesToUpdate;
    QList<IGripItem*> gripsBeingDragged;
    GraphicsRootItem *rootItem;
    QGraphicsPolygonItem *selectionRect;

    GraphicsViewPrivate(GraphicsView *q)
        :   q(q)
        ,   panning(false)
        ,   dragging(false)
        ,   draggingGrips(false)
        ,   rootItem(new GraphicsRootItem)
        ,   selectionRect(new QGraphicsPolygonItem)
    {
        QGraphicsScene *scene = q->scene();
        scene->addItem(rootItem);
        rootItem->setZValue(Q_FLOAT_MAX);
        scene->addItem(selectionRect);
        selectionRect->hide();
    }

    virtual ~GraphicsViewPrivate()
    {}

    void startPan(const QPoint &pos)
    {
        panning = true;
        panStartPos = pos;
        ViewManager *vm = ViewManager::instance();
        panStartCenter.setX(vm->position(q->positionXRole()));
        panStartCenter.setY(vm->position(q->positionYRole()));
    }

    void panTo(const QPoint &pos)
    {
        ViewManager *vm = ViewManager::instance();
        QPointF offset = q->sceneScale().inverted().map(QPointF(pos - panStartPos));
        QPointF center = panStartCenter - offset;
        vm->setPosition(center.x(), q->positionXRole());
        vm->setPosition(center.y(), q->positionYRole());
    }

    void finishPan(const QPoint &pos)
    {
        panTo(pos);
        panning = false;
    }

    void startDraggingGrips()
    {
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->startDraggingPoints();
    }

    void moveGrips(const QPoint &eventPos)
    {
        QPointF pos = rootItem->transform().map(q->mapToScene(eventPos));
        foreach (IGripItem *grip, gripsBeingDragged)
            grip->setPosition(pos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->updatePoints();
    }

    void finishDraggingGrips()
    {
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->finishDraggingPoints();
    }

    bool entityIsSelected(IEntity *entity)
    {
        foreach (GraphicsEntityItem *selectedEntity, selectedEntities)
            if (selectedEntity->entity() == entity)
                return true;
        return false;
    }

    GraphicsEntityItem *findEntityItem(IEntity *entity)
    {
        foreach (GraphicsEntityItem *selectedEntity, selectedEntities)
            if (selectedEntity->entity() == entity)
                return selectedEntity;
        return 0;
    }

    void setSelectedEntities(const QList<IEntity*> &entities)
    {
        clearSelectedEntities();
        appendSelectedEntities(entities);
    }

    void appendSelectedEntities(const QList<IEntity*> &entities)
    {
        foreach (IEntity *entity, entities) {
            if (!entityIsSelected(entity)) {
                GraphicsEntityItem *entityItem = new GraphicsEntityItem(entity);
                selectedEntities.append(entityItem);
                entityItem->setParentItem(rootItem);
                entityItem->highlight();
            }
        }
    }

    void removeSelectedEntities(const QList<IEntity*> &entities)
    {
        foreach (IEntity *entity, entities) {
            GraphicsEntityItem *entityItem = findEntityItem(entity);
            if (entityItem) {
                selectedEntities.removeOne(entityItem);
                entityItem->unhighlight();
                delete entityItem;
            }
        }
    }

    void clearSelectedEntities()
    {
        foreach (GraphicsEntityItem *entityItem, selectedEntities)
            entityItem->unhighlight();
        qDeleteAll(selectedEntities);
        selectedEntities.clear();
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
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setCursor(QPixmap(":/ac_guiplugin/images/crosshair.png"));
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

void GraphicsView::viewSettingsChanged()
{
    d->updateViewSettings();
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    d->updateViewSettings();
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button())
        d->startPan(event->pos());
    else {
        d->dragging = true;
        d->dragOrigin = event->pos();
        QList<QGraphicsItem*> sceneItems = items(QRect(d->dragOrigin.x() - 1, d->dragOrigin.y() - 1, 2, 2));
        foreach (QGraphicsItem *sceneItem, sceneItems) {
            IUnknown *unknownItem = Q_U(sceneItem);
            if (unknownItem) {
                IGripItem *grip = query<IGripItem>(unknownItem);
                if (grip && !d->gripsBeingDragged.contains(grip)) {
                    d->gripsBeingDragged.append(grip);
                    IEntityItem *entity = grip->parentEntityItem();
                    if (!d->entitiesToUpdate.contains(entity))
                        d->entitiesToUpdate.append(entity);
                }
            }
        }
        d->draggingGrips = !d->gripsBeingDragged.isEmpty();
        if (d->draggingGrips)
            d->startDraggingGrips();
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->panning) {
        d->panTo(event->pos());
        emit ViewManager::instance()->viewSettingsChanged();
    } else if (d->draggingGrips) {
        d->moveGrips(event->pos());
    } else if (d->dragging) {
        if (4 <= (event->pos() - d->dragOrigin).manhattanLength()) {
            QRect rect(d->dragOrigin, event->pos());
            QPolygonF polygon = mapToScene(rect.normalized());
            d->selectionRect->setPolygon(polygon);
            d->selectionRect->show();
        }
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button()) {
        d->finishPan(event->pos());
        ViewManager *vm = ViewManager::instance();
        emit vm->viewSettingsChanged();
        vm->updateViewSettings();
    } else {
        if (d->draggingGrips) {
            d->moveGrips(event->pos());
            d->finishDraggingGrips();
        } else {
            QRect rect;
            if ((event->pos() - d->dragOrigin).manhattanLength() < 4)
                rect = QRect(d->dragOrigin.x() - 2, d->dragOrigin.y() - 2, 4, 4);
            else
                rect = QRect(d->dragOrigin, event->pos()).normalized();
            QList<QGraphicsItem*> sceneItems = items(rect);
            QRectF pickRect = sceneTransform().inverted().mapRect(QRectF(rect));
            QList<IEntity*> entities;
            foreach (QGraphicsItem *sceneItem, sceneItems) {
                IUnknown *unknown = Q_U(sceneItem);
                if (unknown) {
                    IEntity *entity = query<IEntity>(unknown);
                    if (entity && entity->intersects(pickRect))
                        entities.append(entity);
                }
            }
            if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
                d->appendSelectedEntities(entities);
            else if (QApplication::keyboardModifiers() & Qt::ControlModifier)
                d->removeSelectedEntities(entities);
            else
                d->setSelectedEntities(entities);
        }
        d->selectionRect->hide();
        d->dragging = false;
        d->draggingGrips = false;
        d->gripsBeingDragged.clear();
        d->entitiesToUpdate.clear();
    }
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (d->panning)
        return;
    qreal scaleAmount = 1.25f;
    if (event->delta() < 0)
        scaleAmount = 1.0f / scaleAmount;
    ViewManager *vm = ViewManager::instance();
    vm->setScale(scaleAmount * vm->scale(scaleXRole()), scaleXRole());
    vm->setScale(scaleAmount * vm->scale(scaleYRole()), scaleYRole());
    emit vm->viewSettingsChanged();
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (d->draggingGrips)
        return;
    if (event->key() == Qt::Key_Escape)
        d->clearSelectedEntities();
}

qreal GraphicsHView::sceneWidth() const
{
    ViewManager *vm = ViewManager::instance();
    return vm->scoreLength() / vm->scale(Ac::TimeScaleRole);
}
