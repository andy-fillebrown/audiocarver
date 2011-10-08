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

static bool gripLessThan(GraphicsGripItem *a, GraphicsGripItem *b)
{
    if (a->pos().x() < b->pos().x())
        return true;
    if (b->pos().x() < a->pos().x())
        return false;
    if (a->pos().y() < b->pos().y())
        return true;
    return false;
}

class GraphicsEntityItemPrivate
{
public:
    GraphicsEntityItem *q;
    IEntity *entity;
    QList<GraphicsGripItem*> gripItems;
    PointList previousPoints;

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

    PointList gripPoints()
    {
        int n = gripItems.count();
        PointList points;
        points.reserve(n);
        qSort(gripItems.begin(), gripItems.end(), gripLessThan);
        for (int i = 0;  i < n;  ++i)
            points.append(Point(gripItems.at(i)->pos(), previousPoints.at(i).curveType));
        return points;
    }

    void updateGripPositions()
    {
        int n = gripItems.count();
        PointList points = entity->points();
        for (int i = 0;  i < n;  ++i)
            gripItems[i]->setPosition(points.at(i).pos);
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

void GraphicsEntityItem::startDraggingPoints()
{
    if (!d->entity)
        return;
    d->previousPoints = d->entity->points();
}

void GraphicsEntityItem::updatePoints()
{
    if (!d->entity)
        return;
    d->entity->setPoints(d->previousPoints, Ac::Dragging);
    d->entity->setPoints(d->gripPoints(), Ac::Dragging);
    d->updateGripPositions();
}

void GraphicsEntityItem::finishDraggingPoints()
{
    if (!d->entity)
        return;
    d->entity->setPoints(d->gripPoints());
}
