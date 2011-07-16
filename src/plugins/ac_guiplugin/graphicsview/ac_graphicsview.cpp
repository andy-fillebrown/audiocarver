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
#include <ac_graphicsitem.h>
#include <QBitmap>
#include <QGraphicsItem>
#include <QMouseEvent>

using namespace Private;

namespace Private {

class AcGraphicsViewData
{
public:
    AcGraphicsView *q;
    bool dragging;
    QPoint dragOrigin;
    QList<AcGraphicsItem*> selectedItems;
    QGraphicsPolygonItem *selectionRect;

    AcGraphicsViewData(AcGraphicsView *q)
        :   q(q)
        ,   dragging(false)
        ,   selectionRect(new QGraphicsPolygonItem)
    {
        q->scene()->addItem(selectionRect);
        selectionRect->hide();
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

} // namespace Private

AcGraphicsView::AcGraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new AcGraphicsViewData(this))
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
}

void AcGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->dragging) {
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
    QList<QGraphicsItem*> sceneItems;
    QRect rect;
    if ((event->pos() - d->dragOrigin).manhattanLength() < 4)
        rect = QRect(d->dragOrigin.x() - 2, d->dragOrigin.y() - 2, 4, 4);
    else
        rect = QRect(d->dragOrigin, event->pos());
    rect = rect.normalized();
    sceneItems = items(rect);
    if (sceneItems.isEmpty()) {
        d->unhighlightSelectedItems();
        d->selectedItems.clear();
    } else {
        foreach (QGraphicsItem *sceneItem, sceneItems) {
            AcGraphicsItem *item = reinterpret_cast<AcGraphicsItem*>(sceneItem->data(0).value<quintptr>());
            if (item)
                d->selectedItems.append(item);
        }
        d->highlightSelectedItems();
    }
    d->selectionRect->hide();
    d->dragging = false;
}
