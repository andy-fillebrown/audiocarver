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

#include "ac_gui_note_entity.h"
#include "ac_gui_namespace.h"
#include "ac_gui_object_entity.h"
#include "ac_gui_object_graphicsitem.h"
#include "ac_gui_object_subentity.h"
#include <ac_core_namespace.h>
#include <mi_core_aggregate.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <QGraphicsLineItem>
#include <QPen>

using namespace Ac;
using namespace Mi;

namespace Note {
namespace Velocity {

class Entity : public Object::Entity
{
    IEntity *_noteEntity;

public:
    Entity(IAggregate *aggregate, IEntity *noteEntity)
        :   Object::Entity(aggregate)
        ,   _noteEntity(noteEntity)
    {}

    IUnknown *initialize()
    {
        return Object::Entity::initialize();
    }

protected:
    QGraphicsItem *graphicsItem(int sceneType, int transformType) const
    {
        return query<IGraphicsItem>(this)->graphicsItem(sceneType, transformType);
    }

    void update(int role)
    {
        switch (role) {
        case VolumeRole: {
            PointList pitch_points = query<IModelData>(query<IModelItem>(_noteEntity)->findItem(PitchCurveItem))->get<PointList>(PointsRole);
            if (pitch_points.isEmpty())
                return;
            qreal volume = query<IModelData>(_noteEntity)->get<qreal>(VolumeRole);
            PointList velocity_line_points;
            qreal x = pitch_points.first().pos.x();
            velocity_line_points.append(Point(x, 0.0f));
            velocity_line_points.append(Point(x, volume));
            query<IGraphicsItem>(this)->setPoints(velocity_line_points);
        } break;
        }
    }

    void highlight()
    {
        query<IGraphicsItem>(this)->highlight();
    }

    void unhighlight()
    {
        query<IGraphicsItem>(this)->unhighlight();
    }

    bool isVisible() const
    {
        return query<IGraphicsItem>(this)->isVisible();
    }
};

class GraphicsItem : public Object::GraphicsItem
{
    QGraphicsLineItem *_graphicsLineItem;

public:
    GraphicsItem(IAggregate *aggregate)
        :   Object::GraphicsItem(aggregate)
        ,   _graphicsLineItem(0)
    {}

    ~GraphicsItem()
    {
        delete _graphicsLineItem;
    }

    IUnknown *initialize()
    {
        _graphicsLineItem = new QGraphicsLineItem;
        _graphicsLineItem->setParentItem(query<IChildEntity>(this)->parent()->graphicsItem(ControlScene, MainTransform));
        _graphicsLineItem->setData(0, quintptr(query<IEntity>(this)));
        return Object::GraphicsItem::initialize();
    }

protected:
    QGraphicsItem *graphicsItem(int sceneType, int transformType) const
    {
        if (ControlScene == sceneType
                && MainTransform == transformType)
            return _graphicsLineItem;
        return 0;
    }

    void setColor(int color)
    {
        QPen pen = _graphicsLineItem->pen();
        pen.setColor(color);
        _graphicsLineItem->setPen(pen);
    }

    void setPoints(const PointList &points)
    {
        QPointF start_point = points.first().pos;
        QPointF end_point = points.last().pos;
        _graphicsLineItem->setLine(start_point.x(), start_point.y(), end_point.x(), end_point.y());
    }

    bool intersects(const QRectF &rect) const
    {
        QLineF line = _graphicsLineItem->line();
        if (rect.contains(line.p1()) && rect.contains(line.p2()))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topLeft(), rect.topRight()), 0))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topRight(), rect.bottomRight()), 0))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomRight(), rect.bottomLeft()), 0))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomLeft(), rect.topLeft()), 0))
            return true;
        return false;
    }

    void highlight()
    {
        QPen pen = _graphicsLineItem->pen();
        pen.setWidth(3.0f);
        _graphicsLineItem->setPen(pen);
    }

    void unhighlight()
    {
        QPen pen = _graphicsLineItem->pen();
        pen.setWidth(1.0f);
        _graphicsLineItem->setPen(pen);
    }

    bool isVisible() const
    {
        return _graphicsLineItem->isVisible();
    }
};

class SubEntity : public Object::SubEntity
{
    IParentEntity *_parent;

public:
    SubEntity(IAggregate *aggregate, IParentEntity *parent)
        :   Object::SubEntity(aggregate)
        ,   _parent(parent)
    {}

    IUnknown *initialize()
    {
        return Object::SubEntity::initialize();
    }

protected:
    IParentEntity *parent() const
    {
        return _parent;
    }

    int sceneType() const
    {
        return ControlScene;
    }

    bool isCurve() const
    {
        return false;
    }
};

}

Entity::~Entity()
{
    delete _velocity;
}

IUnknown *Entity::initialize()
{
    ScoreObject::Entity::initialize();
    _velocity = new Base::Aggregate;
    (new Velocity::Entity(_velocity, this))->initialize();
    (new Velocity::SubEntity(_velocity, this))->initialize();
    (new Velocity::GraphicsItem(_velocity))->initialize();
    update(ColorRole);
    return this;
}

QList<ISubEntity*> Entity::subEntities(int sceneType) const
{
    QList<ISubEntity*> sub_entities = ScoreObject::Entity::subEntities(sceneType);
    if (ControlScene == sceneType)
        sub_entities.append(query<ISubEntity>(velocity()));
    return sub_entities;
}

void Entity::update(int role)
{
    switch (role) {
    case ColorRole: {
        IChildEntity *child_entity = query<IChildEntity>(this);
        if (!child_entity)
            return;
        IModelData *parent_data = query<IModelData>(child_entity->parent());
        if (!parent_data)
            return;
        int color = intFromColor(parent_data->get<QString>(ColorRole));
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            QList<ISubEntity*> sub_entities = subEntities(i);
            foreach (ISubEntity *sub_entity, sub_entities) {
                IGraphicsItem *graphics_item = query<IGraphicsItem>(sub_entity);
                if (!graphics_item)
                    return;
                graphics_item->setColor(color);
            }
        }
    } break;
    default: {
        for (int i = 0;  i < SceneTypeCount;  ++i) {
            QList<ISubEntity*> sub_entities = subEntities(i);
            foreach (ISubEntity *sub_entity, sub_entities) {
                IEntity *entity = query<IEntity>(sub_entity);
                if (!entity)
                    return;
                entity->update(role);
            }
        }
    } break;
    }
}

}
