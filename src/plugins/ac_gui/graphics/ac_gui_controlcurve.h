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

#ifndef AC_GUI_CONTROLCURVE_H
#define AC_GUI_CONTROLCURVE_H

#include "ac_gui_curve.h"

namespace Ac {
namespace Gui {

class ControlCurve : public Curve
{
    friend class GraphicsFactory;

protected:
    IAggregator *init();

    class Entity : public Curve::Entity
    {
        friend class ControlCurve;

    protected:
        Entity(ControlCurve *aggregator)
            :   Curve::Entity(aggregator)
        {}

        IAggregate *init();

        // IEntity
        QGraphicsItem *graphicsItem(int sceneType, int transformType) const
        {
            if (ControlScene == sceneType && MainTransform == transformType)
                return graphicsCurveItem();
            return 0;
        }
    };

    class SubEntity : public Curve::SubEntity
    {
        friend class ControlCurve;

    protected:
        SubEntity(Curve *aggregator)
            :   Curve::SubEntity(aggregator)
        {}

        IAggregate *init();

        // ISubEntity
        int sceneType() const
        {
            return Ac::ControlScene;
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IEntity:
            return appendAggregate((new Entity(this))->init());
        case I::ISubEntity:
            return appendAggregate((new SubEntity(this))->init());
        default:
            return Curve::createAggregate(interfaceType);
        }
    }
};

} // namespace Gui
} // namespace Ac

#endif // AC_GUI_CONTROLCURVE_H
