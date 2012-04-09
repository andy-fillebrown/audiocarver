/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include <ac_namespace.h>

#include <QGraphicsItem>
#include <QGraphicsScene>

GraphicsParent::~GraphicsParent()
{
    qDeleteAll(_unitYGraphicsItems);
    qDeleteAll(_unitXGraphicsItems);
    qDeleteAll(_mainGraphicsItems);
}

static void setParentGraphicsItems(const QMap<int, QGraphicsItem*> &items,
                                   const QMap<int, QGraphicsItem*> &parentItems)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *parent_item = parentItems.value(i, 0);
        QGraphicsItem *item = items.value(i, 0);
        if (item && parent_item)
            item->setParentItem(parent_item);
    }
}

static void clearParentGraphicsItems(const QMap<int, QGraphicsItem*> &items)
{
    for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
        QGraphicsItem *item = items.value(i, 0);
        if (item) {
            item->setParentItem(0);
            QGraphicsScene *scene = item->scene();
            if (scene)
                scene->removeItem(item);
        }
    }
}

void GraphicsParent::updateGraphicsParent()
{
    GraphicsParent *parent = graphicsParent();
    if (parent) {
        setParentGraphicsItems(_mainGraphicsItems, parent->_mainGraphicsItems);
        setParentGraphicsItems(_unitXGraphicsItems, parent->_unitXGraphicsItems);
        setParentGraphicsItems(_unitYGraphicsItems, parent->_unitYGraphicsItems);
    } else {
        clearParentGraphicsItems(_mainGraphicsItems);
        clearParentGraphicsItems(_unitXGraphicsItems);
        clearParentGraphicsItems(_unitYGraphicsItems);
    }
}
