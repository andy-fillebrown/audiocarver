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
    enum { RoleCount = 1 };
    enum { ItemCount = 2 };

    qreal _volume;

    IAggregator *_pitchCurve;
    IAggregator *_controlCurves;

protected:
    enum {
        RoleCountOffset = Object::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount,
        ItemCountOffset = Object::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    ScoreObject()
        :   _volume(0.0f)
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

    PitchCurve *pitchCurve() const
    {
        return cast<PitchCurve>(_pitchCurve);
    }

    ObjectList *controlCurves() const
    {
        return cast<ObjectList>(_controlCurves);
    }

    class AC_CORE_EXPORT ModelData : public Object::ModelData
    {
        ScoreObject *a() const
        {
            return cast<ScoreObject>(Object::ModelData::a());
        }

    public:
        ModelData(ScoreObject *aggregator)
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
            Q_ASSERT(0 <= i);
            switch (i - RoleCountOffset) {
            case 0:
                return Ac::VolumeRole;
            default:
                return Object::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::VolumeRole:
                return a()->volume();
            default:
                return Object::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::VolumeRole:
                return a()->setVolume(qvariant_cast<qreal>(data));
            default:
                return Object::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public Object::ModelItem
    {
        ScoreObject *a() const
        {
            return cast<ScoreObject>(Object::ModelItem::a());
        }

    public:
        ModelItem(Object *aggregator)
            :   Object::ModelItem(aggregator)
        {}

        IAggregate *init();

    protected:
        // IModelItem
        int count() const
        {
            return TotalItemCount;
        }

        int indexOf(const IModelItem *item) const
        {
            const ScoreObject *a = this->a();
            if (query<IModelItem>(a->pitchCurve()) == item)
                return ItemCountOffset;
            if (query<IModelItem>(a->controlCurves()) == item)
                return ItemCountOffset + 1;
            return Object::ModelItem::indexOf(item);
        }

        IModelItem *at(int i) const
        {
            Q_ASSERT(0 <= i);
            switch (i - ItemCountOffset) {
            case 0:
                return query<IModelItem>(a()->pitchCurve());
            case 1:
                return query<IModelItem>(a()->controlCurves());
            default:
                return Object::ModelItem::at(i);
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

#endif // AC_DATABASE_SCOREOBJECT_H
