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

#ifndef AC_DATABASE_PITCHCURVEGUI_H
#define AC_DATABASE_PITCHCURVEGUI_H

#include "ac_database_pitchcurve.h"

#include "ac_database_curvegui.h"

namespace Database {

using namespace CurveGui;

class PitchCurveGui : public PitchCurve
{
    friend class ObjectGuiFactory;

protected:
    PitchCurveGui()
    {}

    IAggregator *init();

    // Object
    void parentChanged(const Object *object, Mi::NotificationFlags notificationFlags)
    {
        if (this == object)
            CurveGui::parentChanged(this);
//        PitchCurve::parentChanged(object, notificationFlags);
    }

    class SubEntity : public CurveGui::SubEntity
    {
        friend class PitchCurveGui;

    protected:
        SubEntity(Curve *aggregator)
            :   CurveGui::SubEntity(aggregator)
        {}

        IAggregate *init();

        // ISubEntity
        int sceneType() const
        {
            return Ac::PitchScene;
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
            return PitchCurve::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_PITCHCURVEGUI_H
