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
#include <QGraphicsItem>
#include <QMouseEvent>

using namespace Private;

namespace Private {

class AcGraphicsViewData
{
public:
    AcGraphicsView *q;

    AcGraphicsViewData(AcGraphicsView *q)
        :   q(q)
    {}
};

} // namespace Private

AcGraphicsView::AcGraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new AcGraphicsViewData(this))
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setCursor(Qt::CrossCursor);
}

AcGraphicsView::~AcGraphicsView()
{
    delete d;
}

void AcGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    QList<QGraphicsItem*> sceneItems = items(QRect(pos.x() - 2, pos.y() - 2, 4, 4));
    foreach (QGraphicsItem *sceneItem, sceneItems) {
        AcGraphicsItem *item = reinterpret_cast<AcGraphicsItem*>(sceneItem->data(0).value<quintptr>());
        if (item)
            item->highlight();
    }
}
