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
#include <ac_graphicspointitem.h>
#include <ac_point.h>
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
    QList<AcGraphicsItem*> selectedItems;
    QList<AcPoint*> pointsBeingDragged;
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

    void setSelectedItems(const QList<AcGraphicsItem*> items)
    {
        unhighlightSelectedItems();
        selectedItems = items;
        highlightSelectedItems();
    }

    void appendSelectedItems(const QList<AcGraphicsItem*> items)
    {
        foreach (AcGraphicsItem *item, items) {
            if (!selectedItems.contains(item)) {
                selectedItems.append(item);
                item->highlight();
            }
        }
    }

    void removeSelectedItems(const QList<AcGraphicsItem*> items)
    {
        foreach (AcGraphicsItem *item, items) {
            if (selectedItems.contains(item)) {
                selectedItems.removeOne(item);
                item->unhighlight();
            }
        }
    }

    void clearSelectedItems()
    {
        unhighlightSelectedItems();
        selectedItems.clear();
    }

    void highlightSelectedItems()
    {
        foreach (AcGraphicsItem *item, selectedItems)
            item->highlight();
    }

    void unhighlightSelectedItems()
    {
        foreach (AcGraphicsItem *item, selectedItems)
            item->unhighlight();
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
        AcGraphicsItem *item = reinterpret_cast<AcGraphicsItem*>(sceneItem->data(0).value<quintptr>());
        AcGraphicsPointItem *pointItem = qobject_cast<AcGraphicsPointItem*>(item);
        if (pointItem) {
            AcPoint *point = pointItem->point();
            if (!d->pointsBeingDragged.contains(point))
                d->pointsBeingDragged.append(point);
        }
    }
    d->draggingPoints = !d->pointsBeingDragged.isEmpty();
}

void AcGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->draggingPoints) {
        QPointF pos = mapToScene(event->pos());
        foreach (AcPoint *point, d->pointsBeingDragged) {
            point->setX(pos.x());
            point->setY(127.0f - pos.y());
        }
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
        foreach (AcPoint *point, d->pointsBeingDragged) {
            point->setX(pos.x());
            point->setY(127.0f - pos.y());
        }
    } else {
        QRect rect;
        if ((event->pos() - d->dragOrigin).manhattanLength() < 4)
            rect = QRect(d->dragOrigin.x() - 1, d->dragOrigin.y() - 1, 2, 2);
        else
            rect = QRect(d->dragOrigin, event->pos()).normalized();
        QList<QGraphicsItem*> sceneItems = items(rect);
        QList<AcGraphicsItem*> items;
        foreach (QGraphicsItem *sceneItem, sceneItems) {
            AcGraphicsItem *item = reinterpret_cast<AcGraphicsItem*>(sceneItem->data(0).value<quintptr>());
            if (item && !items.contains(item)) {
                QRegion region = sceneItem->boundingRegion(viewportTransform());
                if (region.intersects(rect))
                    items.append(item);
            }
        }
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            d->appendSelectedItems(items);
        else if (QApplication::keyboardModifiers() & Qt::ControlModifier)
            d->removeSelectedItems(items);
        else
            d->setSelectedItems(items);
    }
    d->selectionRect->hide();
    d->dragging = false;
    d->draggingPoints = false;
    d->pointsBeingDragged.clear();
}

void AcGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        d->clearSelectedItems();
}
