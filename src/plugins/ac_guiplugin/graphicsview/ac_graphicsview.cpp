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

#include <ac_ientity.h>

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
    QList<IEntity*> selectedEntities;
//    QList<PointItem*> pointsBeingDragged;
//    QList<Curve*> curvesToUpdate;
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

//    void movePoints(const QPoint &eventPos)
//    {
//        QPointF pos = RootItem::xform.map(q->mapToScene(eventPos));
//        foreach (PointItem *point, pointsBeingDragged)
//            point->setPos(pos);
//        foreach (Curve *curve, curvesToUpdate)
//            curve->update();
//    }

    void setSelectedEntities(const QList<IEntity*> entities)
    {
        unhighlightSelectedEntities();
        selectedEntities = entities;
        highlightSelectedEntities();
    }

    void appendSelectedEntities(const QList<IEntity*> entities)
    {
        foreach (IEntity *entity, entities) {
            if (!selectedEntities.contains(entity)) {
                selectedEntities.append(entity);
                entity->highlight();
            }
        }
    }

    void removeSelectedEntities(const QList<IEntity*> entities)
    {
        foreach (IEntity *entity, entities) {
            if (selectedEntities.contains(entity)) {
                selectedEntities.removeOne(entity);
                entity->unhighlight();
            }
        }
    }

    void clearSelectedEntities()
    {
        unhighlightSelectedEntities();
        selectedEntities.clear();
    }

    void highlightSelectedEntities()
    {
        foreach (IEntity *entity, selectedEntities)
            entity->highlight();
    }

    void unhighlightSelectedEntities()
    {
        foreach (IEntity *entity, selectedEntities)
            entity->unhighlight();
    }
};

AcGraphicsView::AcGraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new AcGraphicsViewPrivate(this))
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setCursor(QPixmap(":/ac_guiplugin/images/crosshair.png"));
}

AcGraphicsView::~AcGraphicsView()
{
    delete d;
}

void AcGraphicsView::mousePressEvent(QMouseEvent *event)
{
    d->dragging = true;
    d->dragOrigin = event->pos();
//    QList<QGraphicsItem*> sceneItems = items(QRect(d->dragOrigin.x() - 1, d->dragOrigin.y() - 1, 2, 2));
//    foreach (QGraphicsItem *sceneItem, sceneItems) {
//        GripItem *gripItem = qgraphicsitem_cast<GripItem*>(sceneItem);
//        if (gripItem) {
//            PointItem *point = gripItem->point();
//            if (point && !d->pointsBeingDragged.contains(point)) {
//                d->pointsBeingDragged.append(point);
//                if (!d->curvesToUpdate.contains(point->curve()))
//                    d->curvesToUpdate.append(point->curve());
//            }
//        }
//    }
//    d->draggingPoints = !d->pointsBeingDragged.isEmpty();
}

void AcGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->draggingPoints) {
//        d->movePoints(event->pos());
    }
    else if (d->dragging) {
        if (4 <= (event->pos() - d->dragOrigin).manhattanLength()) {
            QRect rect(d->dragOrigin, event->pos());
            QPolygonF polygon = mapToScene(rect.normalized());
            d->selectionRect->setPolygon(polygon);
            d->selectionRect->show();
        }
    }
}

namespace RootItem {
static const QTransform xform = QTransform::fromScale(1, -1);
}

void AcGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (d->draggingPoints) {
//        d->movePoints(event->pos());
    }
    else {
        QRect rect;
        if ((event->pos() - d->dragOrigin).manhattanLength() < 4)
            rect = QRect(d->dragOrigin.x() - 2, d->dragOrigin.y() - 2, 4, 4);
        else
            rect = QRect(d->dragOrigin, event->pos()).normalized();
        QList<QGraphicsItem*> sceneItems = items(rect);
        QList<IEntity*> entities;
        foreach (QGraphicsItem *sceneItem, sceneItems) {
            IEntity *entity = reinterpret_cast<IEntity*>(sceneItem->data(0).value<quintptr>());
            if (entity && !entities.contains(entity)) {
                QRegion region = sceneItem->boundingRegion(RootItem::xform * viewportTransform());
                if (region.intersects(rect))
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
    d->draggingPoints = false;
//    d->pointsBeingDragged.clear();
//    d->curvesToUpdate.clear();
}

void AcGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        d->clearSelectedEntities();
}
