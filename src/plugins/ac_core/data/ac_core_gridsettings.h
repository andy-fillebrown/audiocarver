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

#ifndef AC_DATABASE_GRIDSETTINGS_H
#define AC_DATABASE_GRIDSETTINGS_H

#include "mi_core_object.h"

#include <ac_corenamespace.h>

namespace Core {

class AC_CORE_EXPORT GridSettings : public Object
{
    friend class ObjectFactory;

    enum { RoleCount = 5 };

    int _snapEnabled : 1;
    int _gridSnapEnabled : 1;
    qreal _timeSnap;
    qreal _pitchSnap;
    qreal _controlSnap;

protected:
    enum {
        RoleCountOffset = Object::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    GridSettings()
        :   _snapEnabled(true)
        ,   _gridSnapEnabled(true)
        ,   _timeSnap(0.125f)
        ,   _pitchSnap(1.0f)
        ,   _controlSnap(0.125f)
    {}

    IAggregator *init();

    bool isSnapEnabled() const
    {
        return _snapEnabled;
    }

    bool setSnapEnabled(bool enabled);

    bool isGridSnapEnabled() const
    {
        return _gridSnapEnabled;
    }

    bool setGridSnapEnabled(bool enabled);

    qreal timeSnap() const
    {
        return _timeSnap;
    }

    bool setTimeSnap(qreal snap);

    qreal pitchSnap() const
    {
        return _pitchSnap;
    }

    bool setPitchSnap(qreal snap);

    qreal controlSnap() const
    {
        return _controlSnap;
    }

    bool setControlSnap(qreal snap);

    class AC_CORE_EXPORT ModelData : public Object::ModelData
    {
        friend class GridSettings;

        GridSettings *a() const
        {
            return static_cast<GridSettings*>(Object::ModelData::a());
        }

    protected:
        ModelData(GridSettings *aggregator)
            :   Object::ModelData(aggregator)
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
                return Ac::SnapEnabledRole;
            case 1:
                return Ac::GridSnapEnabledRole;
            case 2:
                return Ac::TimeSnapRole;
            case 3:
                return Ac::PitchSnapRole;
            case 4:
                return Ac::ControlSnapRole;
            default:
                return Object::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::SnapEnabledRole:
                return a()->isSnapEnabled();
            case Ac::GridSnapEnabledRole:
                return a()->isGridSnapEnabled();
            case Ac::TimeSnapRole:
                return a()->timeSnap();
            case Ac::PitchSnapRole:
                return a()->pitchSnap();
            case Ac::ControlSnapRole:
                return a()->controlSnap();
            default:
                return Object::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::SnapEnabledRole:
                return a()->setSnapEnabled(qvariant_cast<bool>(data));
            case Ac::GridSnapEnabledRole:
                return a()->setGridSnapEnabled(qvariant_cast<bool>(data));
            case Ac::TimeSnapRole:
                return a()->setTimeSnap(qvariant_cast<qreal>(data));
            case Ac::PitchSnapRole:
                return a()->setPitchSnap(qvariant_cast<qreal>(data));
            case Ac::ControlSnapRole:
                return a()->setControlSnap(qvariant_cast<qreal>(data));
            default:
                return Object::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public Object::ModelItem
    {
        friend class GridSettings;

    protected:
        ModelItem(GridSettings *aggregator)
            :   Object::ModelItem(aggregator)
        {}

        IAggregate *init();

        int itemType() const
        {
            return Ac::GridSettingsItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (Ac::GridSettingsItem == itemType)
                return true;
            return Object::ModelItem::isTypeOfItem(itemType);
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
            return Object::createAggregate(interfaceType);
        }
    }
};

} // namespace Core

#endif // AC_DATABASE_GRIDSETTINGS_H




//#ifndef AC_GRIDSETTINGS_H
//#define AC_GRIDSETTINGS_H

//#include <ac_graphicsparent.h>
//#include <ac_namespace.h>

//#include <mi_objectlist.h>

//class ControlGridLine;
//class PitchGridLine;
//class Score;
//class TimeGridLine;

//class GridSettingsPrivate;
//class AC_CORE_EXPORT GridSettings : public GraphicsParent
//{
//    Q_OBJECT
//    Q_PROPERTY(bool snapEnabled READ isSnapEnabled WRITE setSnapEnabled)
//    Q_PROPERTY(bool gridSnapEnabled READ isGridSnapEnabled WRITE setGridSnapEnabled)
//    Q_PROPERTY(qreal timeSnap READ timeSnap WRITE setTimeSnap)
//    Q_PROPERTY(qreal pitchSnap READ pitchSnap WRITE setPitchSnap)
//    Q_PROPERTY(qreal controlSnap READ controlSnap WRITE setControlSnap)

//public:
//    enum { Type = Ac::GridSettingsItem };
//    enum { ModelItemCount = 3 };

//    explicit GridSettings(QObject *parent = 0);

//    Score *score() const;

//    bool isSnapEnabled() const;
//    void setSnapEnabled(bool enabled);
//    bool isGridSnapEnabled() const;
//    void setGridSnapEnabled(bool enabled);
//    qreal timeSnap() const;
//    void setTimeSnap(qreal snap);
//    qreal pitchSnap() const;
//    void setPitchSnap(qreal snap);
//    qreal controlSnap() const;
//    void setControlSnap(qreal snap);

//    ObjectTList<TimeGridLine> *timeGridLines() const;
//    ObjectTList<PitchGridLine> *pitchGridLines() const;
//    ObjectTList<ControlGridLine> *controlGridLines() const;

//    void clear();

//    // IModelItem
//    int type() const { return Type; }
//    int modelItemCount() const { return ModelItemCount; }
//    int modelItemIndex(const IModelItem *item) const;
//    IModelItem *modelItemAt(int i) const;
//    IModelItem *findModelItemList(int type) const;

//    int persistentRoleAt(int i) const
//    {
//        switch (i - staticMetaObject.propertyOffset()) {
//        case 0:
//            return Ac::SnapEnabledRole;
//        case 1:
//            return Ac::GridSnapEnabledRole;
//        case 2:
//            return Ac::TimeSnapRole;
//        case 3:
//            return Ac::PitchSnapRole;
//        case 4:
//            return Ac::ControlSnapRole;
//        default:
//            return GraphicsParent::persistentRoleAt(i);
//        }
//    }

//    QVariant data(int role) const;
//    bool setData(const QVariant &value, int role);

//private:
//    Q_DECLARE_PRIVATE(GridSettings)

//    friend class GridLinePrivate;
//};

//class GridSettingsPrivate : public GraphicsParentPrivate
//{
//    Q_DECLARE_PUBLIC(GridSettings)

//public:
//    uint snapEnabled : 1;
//    uint gridSnapEnabled : bitsizeof(uint) - 1;
//    qreal timeSnap;
//    qreal pitchSnap;
//    qreal controlSnap;
//    ObjectTList<TimeGridLine> *timeGridLines;
//    ObjectTList<PitchGridLine> *pitchGridLines;
//    ObjectTList<ControlGridLine> *controlGridLines;

//    GridSettingsPrivate(GridSettings *q);
//    void init();
//    ~GridSettingsPrivate();

//    GraphicsParentPrivate *graphicsParent() const;
//};

//#endif // AC_GRIDSETTINGS_H
