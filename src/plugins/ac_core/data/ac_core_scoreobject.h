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

#include <mi_core_databaseobject.h>

#include <mi_imodelitemlist.h>

#include "ac_core_constants.h"
#include "ac_core_namespace.h"

namespace Ac {
namespace Core {

class AC_CORE_EXPORT ScoreObject : public Mi::Core::DatabaseObject
{
    enum { RoleCount = 1 };
    enum { ItemCount = 2 };

    qreal _volume;

    IAggregate *_pitchCurve;
    IAggregate *_controlCurves;

protected:
    enum {
        RoleCountOffset = DatabaseObject::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount,
        ItemCountOffset = DatabaseObject::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    ScoreObject()
        :   _volume(DEFAULT_SCOREOBJECT_VOLUME)
        ,   _pitchCurve(0)
        ,   _controlCurves(0)
    {}

    IAggregate *initialize();
    ~ScoreObject();

    qreal volume() const
    {
        return _volume;
    }

    bool setVolume(qreal volume);

    IAggregate *pitchCurve() const
    {
        return _pitchCurve;
    }

    IAggregate *controlCurves() const
    {
        return _controlCurves;
    }

    class AC_CORE_EXPORT ModelData : public DatabaseObject::ModelData
    {
        friend class ScoreObject;

        ScoreObject *aggregate() const
        {
            return static_cast<ScoreObject*>(DatabaseObject::ModelData::aggregate());
        }

    protected:
        ModelData(ScoreObject *aggregate)
            :   DatabaseObject::ModelData(aggregate)
        {}

        IUnknown *initialize();

        // IModelData
        int roleCount() const
        {
            return TotalRoleCount;
        }

        int roleAt(int i) const
        {
            switch (i - RoleCountOffset) {
            case 0:
                return VolumeRole;
            default:
                return DatabaseObject::ModelData::roleAt(i);
            }
        }

        QVariant getValue(int role) const
        {
            switch (role) {
            case VolumeRole:
                return aggregate()->volume();
            default:
                return DatabaseObject::ModelData::getValue(role);
            }
        }

        bool setValue(const QVariant &value, int role)
        {
            switch (role) {
            case VolumeRole:
                return aggregate()->setVolume(qvariant_cast<qreal>(value));
            default:
                return DatabaseObject::ModelData::setValue(value, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public DatabaseObject::ModelItem
    {
        ScoreObject *aggregate() const
        {
            return static_cast<ScoreObject*>(DatabaseObject::ModelItem::aggregate());
        }

    protected:
        ModelItem(ScoreObject *aggregate)
            :   DatabaseObject::ModelItem(aggregate)
        {}

        IUnknown *initialize();

        // IModelItem
        int count() const
        {
            return TotalItemCount;
        }

        int indexOf(const IModelItem *item) const
        {
            const ScoreObject *aggregate = this->aggregate();
            if (query<IModelItem>(aggregate->pitchCurve()) == item)
                return ItemCountOffset;
            if (query<IModelItem>(aggregate->controlCurves()) == item)
                return ItemCountOffset + 1;
            return DatabaseObject::ModelItem::indexOf(item);
        }

        IModelItem *at(int i) const
        {
            switch (i - ItemCountOffset) {
            case 0:
                return query<IModelItem>(aggregate()->pitchCurve());
            case 1:
                return query<IModelItem>(aggregate()->controlCurves());
            default:
                return DatabaseObject::ModelItem::at(i);
            }
        }

        IModelItem *findItem(int itemType) const
        {
            switch (itemType) {
            case PitchCurveItem:
                return query<IModelItem>(aggregate()->pitchCurve());
            default:
                return DatabaseObject::ModelItem::findItem(itemType);
            }
        }

        IModelItemList *findList(int listType) const
        {
            switch (listType) {
            case ControlCurveItem:
                return query<IModelItemList>(aggregate()->controlCurves());
            default:
                return DatabaseObject::ModelItem::findList(listType);
            }
        }
    };

    void clear()
    {
        _controlCurves->clear();
        _pitchCurve->clear();
        setVolume(DEFAULT_SCOREOBJECT_VOLUME);
        Mi::Core::DatabaseObject::clear();
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_SCOREOBJECT_H
