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

#ifndef AC_DATABASE_GUI_CURVE_H
#define AC_DATABASE_GUI_CURVE_H

#include "ac_database_curve.h"
#include "ac_isubentity.h"
#include "ac_ientity.h"

#include <ac_database_curve.h>

#include <ac_graphicsitem.h>
#include <ac_iparententity.h>

namespace Database {
namespace Gui {

class Curve
{
    friend class ControlCurve;
    friend class PitchCurve;

protected:
    class SubEntity : public ISubEntity
    {
    protected:
        Database::Curve *_a;

        SubEntity(Database::Curve *aggregator)
            :   _a(aggregator)
        {}

    public:
        virtual IAggregate *init();

    protected:
        // ISubEntity
        bool isCurve() const
        {
            return true;
        }

        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(_a->parent());
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _a;
        }
    };

    class Entity : public IEntity
    {
        GraphicsCurveItem *_graphicsCurveItem;

    protected:
        Database::Curve *_a;

    public:
        Entity(Database::Curve *aggregator)
            :   _graphicsCurveItem(0)
            ,   _a(aggregator)
        {}

        virtual IAggregate *init();
        ~Entity();

    protected:
        void setPoints(const PointList &points)
        {
            _graphicsCurveItem->setPoints(points);
        }

        void setColor(uint color)
        {
            _graphicsCurveItem->setColor(QColor(QRgb(color)));
        }

        GraphicsCurveItem *graphicsCurveItem() const
        {
            return _graphicsCurveItem;
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
            return _a;
        }
    };
};

} // namespace Gui
} // namespace Database

#endif // AC_DATABASE_GUI_CURVE_H
