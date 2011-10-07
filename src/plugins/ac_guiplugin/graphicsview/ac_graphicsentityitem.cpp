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

#include "ac_graphicsentityitem.h"

#include <ac_graphicsgripitem.h>

#include <ac_ientity.h>

class GraphicsEntityItemPrivate
{
public:
    GraphicsEntityItem *q;
    IEntity *entity;
    QList<GraphicsGripItem*> gripItems;

    GraphicsEntityItemPrivate(GraphicsEntityItem *q)
        :   q(q)
        ,   entity(0)
    {}

    ~GraphicsEntityItemPrivate()
    {
        qDeleteAll(gripItems);
    }

    void addGripItem(GraphicsGripItem *gripItem)
    {
        gripItems.append(gripItem);
        gripItem->setParentItem(q);
    }

    void removeGripItem(GraphicsGripItem *gripItem)
    {
        gripItems.removeOne(gripItem);
        gripItem->setParentItem(0);
    }

    IEntity *entityToHighlight() const
    {
        IEntity *highlightEntity = 0;
        ISubEntity *subEntity = entity ? query<ISubEntity>(entity) : 0;
        if (subEntity)
            highlightEntity = subEntity->parentEntity();
        if (!highlightEntity)
            highlightEntity = entity;
        return highlightEntity;
    }
};

GraphicsEntityItem::GraphicsEntityItem(IEntity *entity)
    :   d(new GraphicsEntityItemPrivate(this))
{
    if (!entity)
        return;
    d->entity = entity;
    PointList points = entity->points();
    foreach (Point point, points)
        d->addGripItem(new GraphicsGripItem(point.pos));
}

GraphicsEntityItem::~GraphicsEntityItem()
{
    delete d;
}

IEntity *GraphicsEntityItem::entity() const
{
    return d->entity;
}

void GraphicsEntityItem::highlight()
{
    IEntity *entity = d->entityToHighlight();
    if (entity)
        entity->highlight();
}

void GraphicsEntityItem::unhighlight()
{
    IEntity *entity = d->entityToHighlight();
    if (entity)
        entity->unhighlight();
}

void GraphicsEntityItem::updatePoints()
{
    if (!d->entity)
        return;
    PointList points = d->entity->points();
    int n = points.count();
    for (int i = 0;  i < n;  ++i)
        points[i].pos = d->gripItems.at(i)->pos();
    d->entity->setPoints(points);
}
