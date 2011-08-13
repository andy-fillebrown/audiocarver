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
#include <ac_item.h>
#include <QApplication>
#include <QBitmap>
#include <QGraphicsItem>
#include <QMouseEvent>

class AcGraphicsViewPrivate
{
public:
    AcGraphicsView *q;
    bool dragging;
    bool draggingPoints;
    QPoint dragOrigin;
    QList<Entity*> selectedObjects;
    QList<PointItem*> pointsBeingDragged;
    QGraphicsPolygonItem *selectionRect;

    AcGraphicsViewPrivate(AcGraphicsView *q)
        :   q(q)
        ,   dragging(false)
        ,   draggingPoints(false)
        ,   selectionRect(new QGraphicsPolygonItem)
    {
        q->scene()->addItem(selectionRect);
        selectionRect->hide();
    }

    virtual ~AcGraphicsViewPrivate()
    {}

    void setSelectedObjects(const QList<Entity*> objects)
    {
        unhighlightSelectedObjects();
        selectedObjects = objects;
        highlightSelectedObjects();
    }

    void appendSelectedObjects(const QList<Entity*> objects)
    {
        foreach (Entity *object, objects) {
            if (!selectedObjects.contains(object)) {
                selectedObjects.append(object);
                object->highlight();
            }
        }
    }

    void removeSelectedObjects(const QList<Entity*> objects)
    {
        foreach (Entity *object, objects) {
            if (selectedObjects.contains(object)) {
                selectedObjects.removeOne(object);
                object->unhighlight();
            }
        }
    }

    void clearSelectedObjects()
    {
        unhighlightSelectedObjects();
        selectedObjects.clear();
    }

    void highlightSelectedObjects()
    {
        foreach (Entity *object, selectedObjects)
            object->highlight();
    }

    void unhighlightSelectedObjects()
    {
        foreach (Entity *object, selectedObjects)
            object->unhighlight();
    }
};

AcGraphicsView::AcGraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new AcGraphicsViewPrivate(this))
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    QBitmap mask(32, 32);
    mask.clear();
    setCursor(QCursor(QBitmap(":/ac_gui/images/crosshair.png"), mask));
}

AcGraphicsView::~AcGraphicsView()
{
    delete d;
}

void AcGraphicsView::mousePressEvent(QMouseEvent *event)
{
    d->dragging = true;
    d->dragOrigin = event->pos();
    QList<QGraphicsItem*> sceneItems = items(QRect(d->dragOrigin.x() - 1, d->dragOrigin.y() - 1, 2, 2));
    foreach (QGraphicsItem *sceneItem, sceneItems) {
        GripItem *gripItem = qgraphicsitem_cast<GripItem*>(sceneItem);
        if (gripItem) {
            PointItem *pointItem = gripItem->point();
            if (pointItem) {
                if (!d->pointsBeingDragged.contains(pointItem))
                    d->pointsBeingDragged.append(pointItem);
            }
        }
    }
    d->draggingPoints = !d->pointsBeingDragged.isEmpty();
}

void AcGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->draggingPoints) {
        QPointF pos = mapToScene(event->pos());
        foreach (PointItem *point, d->pointsBeingDragged) {
            point->setX(pos.x());
            point->setY(-pos.y());
        }
        foreach (PointItem *point, d->pointsBeingDragged)
            point->curve()->update();
    } else if (d->dragging) {
        if (4 <= (event->pos() - d->dragOrigin).manhattanLength()) {
            QRect rect(d->dragOrigin, event->pos());
            QPolygonF polygon = mapToScene(rect.normalized());
            d->selectionRect->setPolygon(polygon);
            d->selectionRect->show();
        }
    }
}

void AcGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (d->draggingPoints) {
        QPointF pos = mapToScene(event->pos());
        foreach (PointItem *point, d->pointsBeingDragged) {
            point->setX(pos.x());
            point->setY(-pos.y());
        }
        foreach (PointItem *point, d->pointsBeingDragged)
            point->curve()->update();
    } else {
        QRect rect;
        if ((event->pos() - d->dragOrigin).manhattanLength() < 4)
            rect = QRect(d->dragOrigin.x() - 1, d->dragOrigin.y() - 1, 2, 2);
        else
            rect = QRect(d->dragOrigin, event->pos()).normalized();
        QList<QGraphicsItem*> sceneItems = items(rect);
        QList<Entity*> objects;
        foreach (QGraphicsItem *sceneItem, sceneItems) {
            Entity *object = reinterpret_cast<Entity*>(sceneItem->data(0).value<quintptr>());
            if (object && !objects.contains(object)) {
                QRegion region = sceneItem->boundingRegion(sceneItem->sceneTransform() * viewportTransform());
                if (region.intersects(rect))
                    objects.append(object);
            }
        }
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            d->appendSelectedObjects(objects);
        else if (QApplication::keyboardModifiers() & Qt::ControlModifier)
            d->removeSelectedObjects(objects);
        else
            d->setSelectedObjects(objects);
    }
    d->selectionRect->hide();
    d->dragging = false;
    d->draggingPoints = false;
    d->pointsBeingDragged.clear();
}

void AcGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        d->clearSelectedObjects();
}
