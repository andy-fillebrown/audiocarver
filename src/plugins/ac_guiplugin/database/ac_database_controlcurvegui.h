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

#ifndef AC_DATABASE_CONTROLCURVEGUI_H
#define AC_DATABASE_CONTROLCURVEGUI_H

#include "ac_database_controlcurve.h"

#include "ac_database_curvegui.h"

#include <ac_guinamespace.h>

namespace Database {

using namespace CurveGui;

class ControlCurveGui : public ControlCurve
{
    friend class ObjectGuiFactory;

protected:
    IAggregator *init();

    // Object
    void parentChanged(const Object *object, Mi::NotificationFlags notificationFlags)
    {
        if (this == object)
            CurveGui::parentChanged(this);
        ControlCurve::parentChanged(object, notificationFlags);
    }

    class SubEntity : public CurveGui::SubEntity
    {
    public:
        SubEntity(Curve *aggregator)
            :   CurveGui::SubEntity(aggregator)
        {}

        IAggregate *init();

    protected:
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
            return ControlCurve::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_CONTROLCURVEGUI_H
