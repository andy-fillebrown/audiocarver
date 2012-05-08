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

namespace CurveGui
{
    class Entity : public IEntity
    {
        Curve *_aggregator;
        GraphicsCurveItem *_graphicsCurveItem;

    public:
        Entity(Curve *aggregator)
            :   _aggregator(aggregator)
            ,   _graphicsCurveItem(0)
        {}

        virtual IAggregate *init();
        ~Entity();

        GraphicsCurveItem *graphicsCurveItem() const
        {
            return _graphicsCurveItem;
        }

    protected:
        Curve *a() const
        {
            return _aggregator;
        }

        void setPoints(const PointList &points)
        {
            _graphicsCurveItem->setPoints(points);
        }

        void setColor(uint color)
        {
            _graphicsCurveItem->setColor(QColor(QRgb(color)));
        }

        // IEntity
        void highlight()
        {
            _graphicsCurveItem->highlight();
        }

        void unhighlight()
        {
            _graphicsCurveItem->unhighlight();
        }

        bool intersects(const QRectF &rect) const
        {
            return _graphicsCurveItem->intersects(rect);
        }

        bool isVisible() const
        {
            return _graphicsCurveItem->isVisible();
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
        GraphicsCurveItem *_graphicsCurveItem;

    public:
        SubEntity(Curve *aggregator)
            :   _aggregator(aggregator)
            ,   _graphicsCurveItem(0)
        {}

        virtual IAggregate *init();

    protected:
        Curve *a() const
        {
            return _aggregator;
        }

        // ISubEntity
        bool intersects(const QRectF &rect) const
        {
            return _graphicsCurveItem->intersects(rect);
        }

        // IChildEntity
        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(a()->parent());
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
