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

#ifndef AC_CORE_SCOREOBJECT_H
#define AC_CORE_SCOREOBJECT_H

#include "mi_core_dataobject.h"

#include <mi_imodellist.h>

#include <ac_core_constants.h>
#include <ac_core_namespace.h>

namespace Ac {
namespace Core {

class AC_CORE_EXPORT ScoreObject : public Mi::Core::DataObject
{
    enum { RoleCount = 1 };
    enum { ItemCount = 2 };

    qreal _volume;

    IAggregator *_pitchCurve;
    IAggregator *_controlCurves;

protected:
    enum {
        RoleCountOffset = DataObject::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount,
        ItemCountOffset = DataObject::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    ScoreObject()
        :   _volume(DEFAULT_SCOREOBJECT_VOLUME)
        ,   _pitchCurve(0)
        ,   _controlCurves(0)
    {}

    IAggregator *init();
    ~ScoreObject();

    qreal volume() const
    {
        return _volume;
    }

    bool setVolume(qreal volume);

    IAggregator *pitchCurve() const
    {
        return _pitchCurve;
    }

    IAggregator *controlCurves() const
    {
        return _controlCurves;
    }

    class AC_CORE_EXPORT ModelData : public DataObject::ModelData
    {
        friend class ScoreObject;

        ScoreObject *a() const
        {
            return static_cast<ScoreObject*>(DataObject::ModelData::a());
        }

    protected:
        ModelData(ScoreObject *aggregator)
            :   DataObject::ModelData(aggregator)
        {}

        IAggregate *init();

        // IModelData
        int roleAt(int i) const
        {
            switch (i - RoleCountOffset) {
            case 0:
                return VolumeRole;
            default:
                return DataObject::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case VolumeRole:
                return a()->volume();
            default:
                return DataObject::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case VolumeRole:
                return a()->setVolume(qvariant_cast<qreal>(data));
            default:
                return DataObject::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public DataObject::ModelItem
    {
        ScoreObject *a() const
        {
            return static_cast<ScoreObject*>(DataObject::ModelItem::a());
        }

    protected:
        ModelItem(DataObject *aggregator)
            :   DataObject::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        int indexOf(const IModelItem *item) const
        {
            const ScoreObject *a = this->a();
            if (query<IModelItem>(a->pitchCurve()) == item)
                return ItemCountOffset;
            if (query<IModelItem>(a->controlCurves()) == item)
                return ItemCountOffset + 1;
            return DataObject::ModelItem::indexOf(item);
        }

        IModelItem *at(int i) const
        {
            switch (i - ItemCountOffset) {
            case 0:
                return query<IModelItem>(a()->pitchCurve());
            case 1:
                return query<IModelItem>(a()->controlCurves());
            default:
                return DataObject::ModelItem::at(i);
            }
        }

        IModelItem *findItem(int itemType) const
        {
            switch (itemType) {
            case PitchCurveItem:
                return query<IModelItem>(a()->pitchCurve());
            default:
                return DataObject::ModelItem::findItem(itemType);
            }
        }

        IModelList *findList(int listType) const
        {
            switch (listType) {
            case ControlCurveItem:
                return query<IModelList>(a()->controlCurves());
            default:
                return DataObject::ModelItem::findList(listType);
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
            return ScoreObject::createAggregate(interfaceType);
        }
    }

    void clear()
    {
        _controlCurves->clear();
        _pitchCurve->clear();
        setVolume(DEFAULT_SCOREOBJECT_VOLUME);
        Mi::Core::DataObject::clear();
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_SCOREOBJECT_H
