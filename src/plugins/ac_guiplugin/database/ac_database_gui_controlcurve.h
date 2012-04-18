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

#ifndef AC_DATABASE_GUI_CONTROLCURVE_H
#define AC_DATABASE_GUI_CONTROLCURVE_H

#include "ac_database_controlcurve.h"
#include "ac_database_gui_curve.h"

#include <ac_guidefs.h>
#include <ac_guinamespace.h>
#include <ac_iparententity.h>

namespace Database {
namespace Gui {

class ControlCurve : public Database::ControlCurve
{
    friend class ObjectFactory;

    Q_IAGGREGATOR_DERIVED(ControlCurve, Database::ControlCurve)

protected:
    ControlCurve()
        :   _entity(0)
    {}

    // Object
    void parentChanged(const Object *object, Mi::NotificationFlags notificationFlags);

    // ISubEntity
    class SubEntity : public Gui::Curve::SubEntity
    {
    public:
        SubEntity(Database::Curve *aggregator)
            :   Gui::Curve::SubEntity(aggregator)
        {}

        // ISubEntity
        int sceneType() const
        {
            return Ac::ControlScene;
        }
    };

    // IEntity
    typedef Gui::Curve::Entity Entity;

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IEntity:
            _entity = new Entity(this);
            _entity->init();
            return appendAggregate(_entity);
        case I::ISubEntity:
            return Q_NEW_AGGREGATE(SubEntity);
        default:
            return Base::createAggregate(interfaceType);
        }
    }

private:
    Entity *_entity;
};

} // namespace Gui
} // namespace Database

#endif // AC_DATABASE_GUI_CONTROLCURVE_H
