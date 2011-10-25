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
#include <ac_viewmanager.h>

#include <ac_ientity.h>

#include <QApplication>
#include <QMouseEvent>

class GraphicsViewPrivate
{
public:
    GraphicsView *q;
    int panning : 1;
    int picking : 1;
    int draggingGrips : 30;
    QPoint panStartPos;
    QPointF panStartCenter;
    QPoint pickStartPos;
    QGraphicsRectItem *pickBox;
    QList<GraphicsEntityItem*> pickedEntities;
    QList<IGripItem*> gripsBeingDragged;
    QList<IEntityItem*> entitiesToUpdate;
    GraphicsRootItem *rootItem;

    GraphicsViewPrivate(GraphicsView *q)
        :   q(q)
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
        QPointF scenePos = rootItem->transform().map(q->mapToScene(pos));
        foreach (IGripItem *grip, gripsBeingDragged)
            grip->setPosition(scenePos);
        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->updatePoints();
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
        pickStartPos = pos;
        picking = true;
    }

    void dragPickBoxTo(const QPoint &pos)
    {
        if (4 <= (pos - pickStartPos).manhattanLength()) {
            QRect pickRect = QRect(pickStartPos, pos).normalized().intersected(pickBoxBounds());
            pickBox->setRect(QRectF(q->mapToScene(pickRect.topLeft()), q->mapToScene(pickRect.bottomRight())));
            pickBox->show();
        }
    }

    void finishPicking(const QPoint &pos)
    {
        bool pickOne = false;
        QRect rect;
        if ((pickOne = (pos - pickStartPos).manhattanLength() < 4))
            rect = QRect(pickStartPos.x() - 2, pickStartPos.y() - 2, 4, 4);
        else
            rect = QRect(pickStartPos, pos).normalized().intersected(pickBoxBounds());
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
        foreach (IEntity *entity, entities) {
            if (!entityIsPicked(entity)) {
                GraphicsEntityItem *item = new GraphicsEntityItem(entity);
                pickedEntities.append(item);
                item->setParentItem(rootItem);
                item->highlight();
            }
        }
    }

    void removePickedEntities(const QList<IEntity*> &entities)
    {
        foreach (IEntity *entity, entities) {
            GraphicsEntityItem *item = findEntityItem(entity);
            if (item) {
                pickedEntities.removeOne(item);
                item->unhighlight();
                delete item;
            }
        }
    }

    void clearPickedEntities()
    {
        foreach (GraphicsEntityItem *item, pickedEntities)
            item->unhighlight();
        qDeleteAll(pickedEntities);
        pickedEntities.clear();
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

void GraphicsView::modelAboutToBeReset()
{
    d->clearPickedEntities();
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
    else if (Qt::LeftButton == event->button()) {
        if (d->selectGrips(event->pos()))
            d->startDraggingGrips();
        else
            d->startPicking(event->pos());
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->panning) {
        d->panTo(event->pos());
        emit ViewManager::instance()->viewSettingsChanged();
    } else if (d->draggingGrips)
        d->dragGripsTo(event->pos());
    else if (d->picking)
        d->dragPickBoxTo(event->pos());
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button()) {
        d->finishPan(event->pos());
        emit ViewManager::instance()->viewSettingsChanged();
    } else if (Qt::LeftButton == event->button()) {
        if (d->draggingGrips)
            d->finishDraggingGrips(event->pos());
        else if (d->picking)
            d->finishPicking(event->pos());
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
    qreal scaleX = scaleAmount * vm->scale(scaleXRole());
    qreal scaleY = scaleAmount * vm->scale(scaleYRole());
    QPointF pos = QPointF(sceneTransform().inverted().map(QPointF(event->pos())) + sceneOffset());
    QPointF center = QPointF(vm->position(positionXRole()), vm->position(positionYRole()));
    QPointF offset = sceneScale().map(center - pos);
    vm->setScale(scaleX, scaleXRole());
    vm->setScale(scaleY, scaleYRole());
    QPointF newCenter = pos + QTransform::fromScale(sceneWidth() / width(), -sceneHeight() / height()).map(offset);
    vm->setPosition(newCenter.x(), positionXRole());
    vm->setPosition(newCenter.y(), positionYRole());
    emit vm->viewSettingsChanged();
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (d->draggingGrips)
        return;
    if (event->key() == Qt::Key_Escape)
        d->clearPickedEntities();
}

qreal GraphicsHView::sceneWidth() const
{
    ViewManager *vm = ViewManager::instance();
    return vm->scoreLength() / vm->scale(Ac::TimeScaleRole);
}
