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

#ifndef AC_PITCHCURVEGRAPHICSOBJECT_H
#define AC_PITCHCURVEGRAPHICSOBJECT_H

#include "ac_abstractcurvegraphicsobject.h"
#include "ac_pitchcurvedataobject.h"

class AC_CORE_EXPORT PitchCurveGraphicsObject : public PitchCurveDataObject
{
    friend class GuiDataObjectFactory;

    Q_IAGGREGATOR_DERIVED(PitchCurveGraphicsObject, PitchCurveDataObject)

protected:
    PitchCurveGraphicsObject()
        :   _entity(0)
    {}

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IEntity:
            _entity = new CurveEntity(this);
            _entity->init();
            return appendAggregate(_entity);
        case I::ISubEntity:
            return Q_NEW_AGGREGATE(PitchCurveSubEntity);
        default:
            return Base::createAggregate(interfaceType);
        }
    }

private:
    CurveEntity *_entity;
};

#endif // AC_PITCHCURVEGRAPHICS_H
