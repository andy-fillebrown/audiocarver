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

#ifndef AC_SCOREOBJECT_H
#define AC_SCOREOBJECT_H

#include "ac_graphicsparent.h"

#include <ac_namespace.h>
#include <ac_pitchcurve.h>

#include <mi_dataobjectlist.h>

class ControlCurve;
class PitchCurve;

class QGraphicsItem;

class AC_CORE_EXPORT ScoreObject : public GraphicsParent
{
    Q_I_DERIVED__AGGREGATOR(ScoreObject, GraphicsParent)

    Q_I_DERIVED__AGGREGATOR__ROLE_COUNT(1)
    qreal _volume;

    Q_I_DERIVED__AGGREGATOR__ITEM_COUNT(2)
    QScopedPointer<PitchCurve> _pitchCurve;
    QScopedPointer<DataObjectList> _controlCurves;

protected:
    ScoreObject()
        :   _volume(0.0f)
    {}

    qreal volume() const
    {
        return _volume;
    }

    bool setVolume(qreal volume)
    {
        volume = qMin(qMax(qreal(0.0f), volume), qreal(1.0f));
        if (_volume == volume)
            return false;
        Q_SCOPED_CHANGE(Ac::VolumeRole);
        _volume = volume;
        updatePoints();
        return true;
    }

    PitchCurve *pitchCurve() const
    {
        return qGetPtrHelper(_pitchCurve);
    }

    DataObjectList *controlCurves() const
    {
        return qGetPtrHelper(_controlCurves);
    }

    virtual qreal length() const = 0;

public:
    virtual void updatePoints() {}

protected:
    // IAggregator

    void *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelData:
            Q_ASSERT(0);  return 0;
        case I::IModelItem:
            Q_ASSERT(0);  return 0;
        default:
            return Base::createAggregate(interfaceType);
        }
    }

    class ModelData : public Base::ModelData
    {
        Q_I_DERIVED__MODEL_DATA
        Q_I_DERIVED__MODEL_DATA__ROLE_FUNCTIONS

        // IModelData

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

    class ModelItem : public Base::ModelItem
    {
        Q_I_DERIVED__MODEL_ITEM
        Q_I_DERIVED__MODEL_ITEM__ALL_FUNCTIONS
    };
};

#endif // AC_SCOREOBJECT_H
