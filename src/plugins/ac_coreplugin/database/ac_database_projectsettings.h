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

#ifndef AC_DATABASE_PROJECTSETTINGS_H
#define AC_DATABASE_PROJECTSETTINGS_H

#include "mi_database_object.h"

#include <ac_corenamespace.h>

namespace Database {

class ProjectSettings : public Object
{
    friend class ObjectFactory;

    enum { RoleCount = 3 };

    int _sampleRate;
    int _controlRate;
    int _curveRate;

protected:
    enum {
        RoleCountOffset = Object::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ProjectSettings()
        :   _sampleRate(48000)
        ,   _controlRate(4800)
        ,   _curveRate(48)
    {}

    IAggregator *init();

    int sampleRate() const
    {
        return _sampleRate;
    }

    bool setSampleRate(int rate);

    int controlRate() const
    {
        return _controlRate;
    }

    bool setControlRate(int rate);

    int curveRate() const
    {
        return _curveRate;
    }

    bool setCurveRate(int rate);

    class AC_CORE_EXPORT ModelData : public Object::ModelData
    {
        ProjectSettings *a() const
        {
            return static_cast<ProjectSettings*>(Object::ModelData::a());
        }

    public:
        ModelData(ProjectSettings *aggregator)
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
            Q_ASSERT(i <= 0);
            switch (i - RoleCountOffset) {
            case 0:
                return Ac::SampleRateRole;
            case 1:
                return Ac::ControlRateRole;
            case 2:
                return Ac::CurveRateRole;
            default:
                return Object::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::SampleRateRole:
                return a()->sampleRate();
            case Ac::ControlRateRole:
                return a()->controlRate();
            case Ac::CurveRateRole:
                return a()->curveRate();
            default:
                return Object::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::SampleRateRole:
                return a()->setSampleRate(qvariant_cast<int>(data));
            case Ac::ControlRateRole:
                return a()->setControlRate(qvariant_cast<int>(data));
            case Ac::CurveRateRole:
                return a()->setCurveRate(qvariant_cast<int>(data));
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

#endif // AC_DATABASE_PROJECTSETTINGS_H