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

#ifndef AC_DATABASE_VIEWSETTINGS_H
#define AC_DATABASE_VIEWSETTINGS_H

#include "mi_database_object.h"

#include <ac_coreconstants.h>
#include <ac_corenamespace.h>

namespace Database {

class ViewSettings : public Object
{
    friend class ObjectFactory;

    enum { RoleCount = 6 };

    qreal _timePosition;
    qreal _pitchPosition;
    qreal _controlPosition;
    qreal _timeScale;
    qreal _pitchScale;
    qreal _controlScale;

protected:
    enum {
        RoleCountOffset = Object::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ViewSettings()
        :   _timePosition(30.0f)
        ,   _pitchPosition(63.5f)
        ,   _controlPosition(0.5f)
        ,   _timeScale(VIEWSCALE_MIN)
        ,   _pitchScale(VIEWSCALE_MIN)
        ,   _controlScale(VIEWSCALE_MIN)
    {}

    IAggregator *init();

    qreal timePosition() const
    {
        return _timePosition;
    }

    bool setTimePosition(qreal position);

    qreal pitchPosition() const
    {
        return _pitchPosition;
    }

    bool setPitchPosition(qreal position);

    qreal controlPosition() const
    {
        return _controlPosition;
    }

    bool setControlPosition(qreal position);

    qreal timeScale() const
    {
        return _timeScale;
    }

    bool setTimeScale(qreal scale);

    qreal pitchScale() const
    {
        return _pitchScale;
    }

    bool setPitchScale(qreal scale);

    qreal controlScale() const
    {
        return _controlScale;
    }

    bool setControlScale(qreal scale);

    class ModelData : public Object::ModelData
    {
        ViewSettings *a() const
        {
            return static_cast<ViewSettings*>(Object::ModelData::a());
        }

    public:
        ModelData(ViewSettings *aggregator)
            :   Object::ModelData(aggregator)
        {}

        IAggregate *init();

    protected:
        // IModelData
        int roleCount() const
        {
            return TotalRoleCount;
        }

        int roleAt(int i) const
        {
            switch (i - RoleCountOffset) {
            case 0:
                return Ac::TimePositionRole;
            case 1:
                return Ac::PitchPositionRole;
            case 2:
                return Ac::ControlPositionRole;
            case 3:
                return Ac::TimeScaleRole;
            case 4:
                return Ac::PitchScaleRole;
            case 5:
                return Ac::ControlScaleRole;
            default:
                return Object::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::TimePositionRole:
                return a()->timePosition();
            case Ac::PitchPositionRole:
                return a()->pitchPosition();
            case Ac::ControlPositionRole:
                return a()->controlPosition();
            case Ac::TimeScaleRole:
                return a()->timeScale();
            case Ac::PitchScaleRole:
                return a()->pitchScale();
            case Ac::ControlScaleRole:
                return a()->controlScale();
            default:
                return Object::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::TimePositionRole:
                return a()->setTimePosition(qvariant_cast<qreal>(data));
            case Ac::PitchPositionRole:
                return a()->setPitchPosition(qvariant_cast<qreal>(data));
            case Ac::ControlPositionRole:
                return a()->setControlPosition(qvariant_cast<qreal>(data));
            case Ac::TimeScaleRole:
                return a()->setTimeScale(qvariant_cast<qreal>(data));
            case Ac::PitchScaleRole:
                return a()->setPitchScale(qvariant_cast<qreal>(data));
            case Ac::ControlScaleRole:
                return a()->setControlScale(qvariant_cast<qreal>(data));
            default:
                return Object::ModelData::setVariant(data, role);
            }
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelData:
            return appendAggregate((new ModelData(this))->init());
        default:
            return Object::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

#endif // AC_DATABASE_VIEWSETTINGS_H
