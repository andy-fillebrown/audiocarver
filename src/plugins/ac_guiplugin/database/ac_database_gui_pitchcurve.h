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

#ifndef AC_DATABASE_GUI_PITCHCURVE_H
#define AC_DATABASE_GUI_PITCHCURVE_H

#include "ac_database_pitchcurve.h"
#include "ac_database_gui_curve.h"

namespace Database {
namespace Gui {

class PitchCurve : public Database::PitchCurve
{
    friend class ObjectFactory;

    Q_IAGGREGATOR_DERIVED(PitchCurve, Database::PitchCurve)

protected:
    PitchCurve()
        :   _entity(0)
    {}

    // ISubEntity
    class SubEntity : public Gui::Curve::SubEntity
    {
    public:
        SubEntity(Database::Curve *aggregator)
            :   Gui::Curve::SubEntity(aggregator)
        {}

    protected:
        // ISubEntity
        int sceneType() const
        {
            return Ac::PitchScene;
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

#endif // AC_DATABASE_GUI_PITCHCURVE_H
