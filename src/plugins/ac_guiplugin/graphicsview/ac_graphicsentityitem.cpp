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

    void clearGripItems()
    {
        qDeleteAll(gripItems);
        gripItems.clear();
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
        const int n = gripItems.count();
        PointList points;
        points.reserve(n);
        qSort(gripItems.begin(), gripItems.end(), gripLessThan);
        for (int i = 0;  i < n;  ++i) {
            Ac::CurveType curve_type = Ac::NoCurve;
            if (i < previousPoints.count())
                curve_type = previousPoints.at(i).curveType;
            points.append(Point(gripItems.at(i)->pos(), curve_type));
        }
        return points;
    }

    void updateGripPositions()
    {
        const int n = gripItems.count();
        PointList points = entity->points();
        for (int i = 0;  i < n;  ++i)
            gripItems[i]->setPosition(points.at(i).pos);
    }
};

GraphicsEntityItem::GraphicsEntityItem(IEntity *entity)
    :   d(new GraphicsEntityItemPrivate(this))
{
    d->entity = entity;
    resetGrips();
}

GraphicsEntityItem::~GraphicsEntityItem()
{
    delete d;
}

void GraphicsEntityItem::resetGrips()
{
    const PointList &points = d->entity->points();
    const int points_n = points.count();

    for (int i = 0;  i < points_n;  ++i) {
        if (i < d->gripItems.count()) {
            IGripItem *gripItem = d->gripItems[i];
            gripItem->setPosition(points.at(i).pos);
            gripItem->updateOriginalPosition();
        } else
            d->addGripItem(new GraphicsGripItem(points.at(i).pos));
    }

    for (int i = 0;  i < points_n;  ++i)
        d->gripItems[i]->show();

    const int grips_n = d->gripItems.count();
    for (int i = points_n;  i < grips_n;  ++i)
        d->gripItems[i]->hide();
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

    foreach (GraphicsGripItem *gripItem, d->gripItems)
        gripItem->updateOriginalPosition();
}
