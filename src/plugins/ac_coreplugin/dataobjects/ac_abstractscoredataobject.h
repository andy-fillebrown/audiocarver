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

#ifndef AC_ABSTRACTSCOREDATAOBJECT_H
#define AC_ABSTRACTSCOREDATAOBJECT_H

#include "mi_dataobject.h"

#include <ac_pitchcurvedataobject.h>

#include <mi_dataobjectlist.h>

class AC_CORE_EXPORT AbstractScoreDataObject : public DataObject
{
    Q_IAGGREGATOR_DERIVED(AbstractScoreDataObject, DataObject)

    qreal _volume;
    Q_IAGGREGATOR_DERIVED__ROLECOUNT(1)

    IAggregator *_pitchCurve;
    IAggregator *_controlCurves;
    Q_IAGGREGATOR_DERIVED__ITEMCOUNT(2)

protected:
    AbstractScoreDataObject()
        :   _volume(0.0f)
        ,   _pitchCurve(0)
        ,   _controlCurves(0)
    {}

    ~AbstractScoreDataObject();

    virtual qreal length() const = 0;
    virtual void updatePoints() {}

    qreal volume() const
    {
        return _volume;
    }

    bool setVolume(qreal volume);

    PitchCurveDataObject *pitchCurve() const
    {
        return cast<PitchCurveDataObject>(_pitchCurve);
    }

    DataObjectList *controlCurves() const
    {
        return cast<DataObjectList>(_controlCurves);
    }

    // IModelData
    class ModelData : public Base::ModelData
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
    class ModelItem : public Base::ModelItem
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

#endif // AC_ABSTRACTSCOREDATAOBJECT_H
