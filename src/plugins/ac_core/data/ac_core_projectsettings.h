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

#ifndef AC_CORE_PROJECTSETTINGS_H
#define AC_CORE_PROJECTSETTINGS_H

#include "mi_core_dataobject.h"

#include <ac_core_constants.h>
#include <ac_core_namespace.h>

namespace Ac {
namespace Core {

class AC_CORE_EXPORT ProjectSettings : public Mi::Core::DataObject
{
    friend class DataObjectFactory;

    enum { RoleCount = 3 };

    int _sampleRate;
    int _controlRate;
    int _curveRate;

protected:
    enum {
        RoleCountOffset = DataObject::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    ProjectSettings()
        :   _sampleRate(DEFAULT_PROJECTSETTINGS_SAMPLERATE)
        ,   _controlRate(DEFAULT_PROJECTSETTINGS_CONTROLRATE)
        ,   _curveRate(DEFAULT_PROJECTSETTINGS_CURVERATE)
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

    class AC_CORE_EXPORT ModelData : public DataObject::ModelData
    {
        friend class ProjectSettings;

        ProjectSettings *a() const
        {
            return static_cast<ProjectSettings*>(DataObject::ModelData::a());
        }

    protected:
        ModelData(ProjectSettings *aggregator)
            :   DataObject::ModelData(aggregator)
        {}

        IAggregate *init();

        // IModelData
        int roleCount() const
        {
            return TotalRoleCount;
        }

        int roleAt(int i) const
        {
            switch (i - RoleCountOffset) {
            case 0:
                return SampleRateRole;
            case 1:
                return ControlRateRole;
            case 2:
                return CurveRateRole;
            default:
                return DataObject::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case SampleRateRole:
                return a()->sampleRate();
            case ControlRateRole:
                return a()->controlRate();
            case CurveRateRole:
                return a()->curveRate();
            default:
                return DataObject::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case SampleRateRole:
                return a()->setSampleRate(qvariant_cast<int>(data));
            case ControlRateRole:
                return a()->setControlRate(qvariant_cast<int>(data));
            case CurveRateRole:
                return a()->setCurveRate(qvariant_cast<int>(data));
            default:
                return DataObject::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public DataObject::ModelItem
    {
        friend class ProjectSettings;

    protected:
        ModelItem(ProjectSettings *aggregator)
            :   DataObject::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        int itemType() const
        {
            return ProjectSettingsItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (ProjectSettingsItem == itemType)
                return true;
            return DataObject::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelData:
            return appendAggregate((new ModelData(this))->init());
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return DataObject::createAggregate(interfaceType);
        }
    }

    void clear()
    {
        setCurveRate(DEFAULT_PROJECTSETTINGS_CURVERATE);
        setControlRate(DEFAULT_PROJECTSETTINGS_CONTROLRATE);
        setSampleRate(DEFAULT_PROJECTSETTINGS_SAMPLERATE);
        Mi::Core::DataObject::clear();
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_PROJECTSETTINGS_H
