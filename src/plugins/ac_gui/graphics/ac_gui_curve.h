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

#ifndef AC_GUI_CURVE_H
#define AC_GUI_CURVE_H

#include "ac_gui_graphicsobject.h"

#include "ac_isubentity.h"
#include "ac_ientity.h"

#include <ac_iparententity.h>

#include <mi_imodelitem.h>

#include <ac_gui_graphicsitem.h>

namespace Ac {
namespace Gui {

class Curve : public GraphicsObject
{
protected:
    class SubEntity;

    Curve()
    {}

    virtual IAggregator *init();

    class Entity : public IEntity
    {
        friend class Curve;
        friend class SubEntity;

        Curve *_aggregator;
        GraphicsCurveItem *_graphicsCurveItem;

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
        void update(int role);

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
};

} // namespace Gui
} // namespace Ac

#endif // AC_GUI_CURVE_H
