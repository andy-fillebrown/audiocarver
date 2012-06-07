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

#include "ac_database_curvegui.h"

#include <ac_database_scoreobjectgui.h>

#include <QGraphicsScene>

namespace Database {

static void setGraphicsItemParent(IParentEntity *parent, IEntity *curve)
{
    ScoreObjectGui::ParentEntity *parent_implementation = dynamic_cast<ScoreObjectGui::ParentEntity*>(parent);
    if (!parent_implementation)
        return;
    CurveGui::Entity *curve_implementation = dynamic_cast<CurveGui::Entity*>(curve);
    if (!curve_implementation)
        return;
    curve_implementation->graphicsCurveItem()->setParentItem(parent_implementation->mainGraphicsItems().value((query<ISubEntity>(curve))->sceneType()));
}

static void clearGraphicsItemParent(IEntity *curve)
{
    CurveGui::Entity *curve_implementation = dynamic_cast<CurveGui::Entity*>(curve);
    if (!curve_implementation)
        return;
    QGraphicsItem *item = curve_implementation->graphicsCurveItem();
    if (!item)
        return;
    item->setParentItem(0);
    QGraphicsScene *scene = item->scene();
    if (scene)
        scene->removeItem(item);
}

void CurveGui::parentChanged(Curve *curve)
{
    Object *parent = curve->parent();
    if (parent)
        setGraphicsItemParent(query<IParentEntity>(parent), query<IEntity>(curve));
    else
        clearGraphicsItemParent(query<IEntity>(curve));
}

IAggregate *CurveGui::Entity::init()
{
    _graphicsCurveItem = new GraphicsCurveItem;
    _graphicsCurveItem->setEntity(this);
    return this;
}

CurveGui::Entity::~Entity()
{
    delete _graphicsCurveItem;
}

IAggregate *CurveGui::SubEntity::init()
{
    _graphicsCurveItem = (cast<CurveGui::Entity>(query<IEntity>(a())))->graphicsCurveItem();
    return this;
}

} // namespace Database