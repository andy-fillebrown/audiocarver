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

#ifndef AC_DATABASE_CURVEGUI_H
#define AC_DATABASE_CURVEGUI_H

#include "ac_database_curve.h"

#include "ac_isubentity.h"
#include "ac_ientity.h"

#include <ac_database_curve.h>

#include <ac_graphicsitem.h>
#include <ac_iparententity.h>

namespace Database {

class ControlCurveGui;
class PitchCurveGui;

namespace CurveGui
{
    void parentChanged(Curve *curve);

    class Entity : public IEntity
    {
        friend class Database::ControlCurveGui;
        friend class Database::PitchCurveGui;
        friend class SubEntity;

        Curve *_aggregator;
        GraphicsCurveItem *_graphicsCurveItem;

    public:
        static void setGraphicsItemParent(IParentEntity *parent, IEntity *curve);
        static void clearGraphicsItemParent(IEntity *curve);

    protected:
        Entity(Curve *aggregator)
            :   _aggregator(aggregator)
            ,   _graphicsCurveItem(0)
        {}

        virtual IAggregate *init();
        ~Entity();

        Curve *a() const
        {
            return _aggregator;
        }

        GraphicsCurveItem *graphicsCurveItem() const
        {
            return _graphicsCurveItem;
        }

        void setPoints(const PointList &points)
        {
            graphicsCurveItem()->setPoints(points);
        }

        void setColor(uint color)
        {
            graphicsCurveItem()->setColor(QColor(QRgb(color)));
        }

        // IEntity
        void highlight()
        {
            graphicsCurveItem()->highlight();
        }

        void unhighlight()
        {
            graphicsCurveItem()->unhighlight();
        }

        bool intersects(const QRectF &rect) const
        {
            return graphicsCurveItem()->intersects(rect);
        }

        bool isVisible() const
        {
            return graphicsCurveItem()->isVisible();
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    class SubEntity : public ISubEntity
    {
        Curve *_aggregator;

        Entity *entity() const
        {
            return dynamic_cast<Entity*>(query<IEntity>(_aggregator));
        }

        GraphicsCurveItem *graphicsCurveItem() const
        {
            return entity()->graphicsCurveItem();
        }

    protected:
        SubEntity(Curve *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

        Curve *a() const
        {
            return _aggregator;
        }

        // ISubEntity
        bool intersects(const QRectF &rect) const
        {
            return graphicsCurveItem()->intersects(rect);
        }

        // IChildEntity
        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(query<IModelItem>(a())->parent());
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };
}

} // namespace Database

#endif // AC_DATABASE_CURVEGUI_H
