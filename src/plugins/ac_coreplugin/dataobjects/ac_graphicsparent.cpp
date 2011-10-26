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

#include "ac_graphicsparent.h"

#include <QGraphicsItem>

static void setParentGraphicsItems(const QMap<int, QGraphicsItem*> &items,
                                   const QMap<int, QGraphicsItem*> &parentItems)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *parentItem = parentItems.value(i, 0);
        QGraphicsItem *item = items.value(i, 0);
        if (item && parentItem)
            item->setParentItem(parentItem);
    }
}

static void clearParentGraphicsItems(const QMap<int, QGraphicsItem*> &items)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *item = items.value(i, 0);
        if (item)
            item->setParentItem(0);
    }
}

GraphicsParentPrivate::GraphicsParentPrivate(GraphicsObject *q)
    :   GraphicsObjectPrivate(q)
{}

void GraphicsParentPrivate::init()
{
    updateGraphicsParent();
}

GraphicsParentPrivate::~GraphicsParentPrivate()
{
    qDeleteAll(unitYGraphicsItems);
    qDeleteAll(unitXGraphicsItems);
    qDeleteAll(mainGraphicsItems);
}

void GraphicsParentPrivate::updateGraphicsParent()
{
    GraphicsParentPrivate *parent = graphicsParent();
    if (parent) {
        setParentGraphicsItems(mainGraphicsItems, parent->mainGraphicsItems);
        setParentGraphicsItems(unitXGraphicsItems, parent->unitXGraphicsItems);
        setParentGraphicsItems(unitYGraphicsItems, parent->unitYGraphicsItems);
    } else {
        clearParentGraphicsItems(mainGraphicsItems);
        clearParentGraphicsItems(unitXGraphicsItems);
        clearParentGraphicsItems(unitYGraphicsItems);
    }
}

GraphicsParent::GraphicsParent(GraphicsParentPrivate &dd, QObject *parent)
    :   GraphicsObject(dd, parent)
{
    dd.init();
}
