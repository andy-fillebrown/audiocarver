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

#ifndef AC_DATABASE_SCOREOBJECT_H
#define AC_DATABASE_SCOREOBJECT_H

#include "mi_database_object.h"

#include <ac_database_pitchcurve.h>

#include <mi_database_objectlist.h>

namespace Database {

class AC_CORE_EXPORT ScoreObject : public Object
{
    Q_IAGGREGATOR_DERIVED(ScoreObject, Object)

    qreal _volume;
    Q_IAGGREGATOR_DERIVED__ROLECOUNT(1)

    IAggregator *_pitchCurve;
    IAggregator *_controlCurves;
    Q_IAGGREGATOR_DERIVED__ITEMCOUNT(2)

protected:
    ScoreObject()
        :   _volume(0.0f)
        ,   _pitchCurve(0)
        ,   _controlCurves(0)
    {}

    ~ScoreObject();

    virtual qreal length() const = 0;
    virtual void updatePoints() {}

    qreal volume() const
    {
        return _volume;
    }

    bool setVolume(qreal volume);

    PitchCurve *pitchCurve() const
    {
        return cast<PitchCurve>(_pitchCurve);
    }

    ObjectList *controlCurves() const
    {
        return cast<ObjectList>(_controlCurves);
    }

    // IModelData
    class AC_CORE_EXPORT ModelData : public Base::ModelData
    {
        Q_IMODELDATA_DERIVED
        Q_IMODELDATA_DERIVED__ROLE_FUNCTIONS

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::VolumeRole:
                return a()->volume();
            default:
                return Base::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::VolumeRole:
                return a()->setVolume(qvariant_cast<qreal>(data));
            default:
                return Base::setVariant(data, role);
            }
        }
    };

    // IModelItem
    class AC_CORE_EXPORT ModelItem : public Base::ModelItem
    {
        Q_IMODELITEM_DERIVED
        Q_IMODELITEM_DERIVED__FUNCTIONS
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelData:
            return Q_NEW_AGGREGATE(ModelData);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_SCOREOBJECT_H
