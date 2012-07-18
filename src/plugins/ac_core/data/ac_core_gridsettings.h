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

#ifndef AC_CORE_GRIDSETTINGS_H
#define AC_CORE_GRIDSETTINGS_H

#include "mi_core_dataobject.h"

#include <mi_imodellist.h>

#include <ac_core_constants.h>
#include <ac_core_namespace.h>

namespace Ac {
namespace Core {

class AC_CORE_EXPORT GridSettings : public Mi::Core::DataObject
{
    friend class DataObjectFactory;

    enum { RoleCount = 5 };
    enum { ItemCount = 3 };

    int _snapEnabled : 1;
    int _gridSnapEnabled : 1;
    qreal _timeSnap;
    qreal _pitchSnap;
    qreal _controlSnap;

    IAggregator *_timeGridLines;
    IAggregator *_pitchGridLines;
    IAggregator *_controlGridLines;

protected:
    enum {
        RoleCountOffset = DataObject::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount,
        ItemCountOffset = DataObject::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    GridSettings()
        :   _snapEnabled(DEFAULT_GRIDSETTINGS_SNAPENABLED)
        ,   _gridSnapEnabled(DEFAULT_GRIDSETTINGS_GRIDSNAPENABLED)
        ,   _timeSnap(DEFAULT_GRIDSETTINGS_TIMESNAP)
        ,   _pitchSnap(DEFAULT_GRIDSETTINGS_PITCHSNAP)
        ,   _controlSnap(DEFAULT_GRIDSETTINGS_CONTROLSNAP)
        ,   _timeGridLines(0)
        ,   _pitchGridLines(0)
        ,   _controlGridLines(0)
    {}

    IAggregator *init();
    ~GridSettings();

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

    IAggregator *timeGridLines() const
    {
        return _timeGridLines;
    }

    IAggregator *pitchGridLines() const
    {
        return _pitchGridLines;
    }

    IAggregator *controlGridLines() const
    {
        return _controlGridLines;
    }

    class AC_CORE_EXPORT ModelData : public DataObject::ModelData
    {
        friend class GridSettings;

        GridSettings *a() const
        {
            return static_cast<GridSettings*>(DataObject::ModelData::a());
        }

    protected:
        ModelData(GridSettings *aggregator)
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
                return SnapEnabledRole;
            case 1:
                return GridSnapEnabledRole;
            case 2:
                return TimeSnapRole;
            case 3:
                return PitchSnapRole;
            case 4:
                return ControlSnapRole;
            default:
                return DataObject::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case SnapEnabledRole:
                return a()->isSnapEnabled();
            case GridSnapEnabledRole:
                return a()->isGridSnapEnabled();
            case TimeSnapRole:
                return a()->timeSnap();
            case PitchSnapRole:
                return a()->pitchSnap();
            case ControlSnapRole:
                return a()->controlSnap();
            default:
                return DataObject::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case SnapEnabledRole:
                return a()->setSnapEnabled(qvariant_cast<bool>(data));
            case GridSnapEnabledRole:
                return a()->setGridSnapEnabled(qvariant_cast<bool>(data));
            case TimeSnapRole:
                return a()->setTimeSnap(qvariant_cast<qreal>(data));
            case PitchSnapRole:
                return a()->setPitchSnap(qvariant_cast<qreal>(data));
            case ControlSnapRole:
                return a()->setControlSnap(qvariant_cast<qreal>(data));
            default:
                return DataObject::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public DataObject::ModelItem
    {
        friend class GridSettings;

        GridSettings *a() const
        {
            return static_cast<GridSettings*>(DataObject::ModelItem::a());
        }

    protected:
        ModelItem(GridSettings *aggregator)
            :   DataObject::ModelItem(aggregator)
        {}

        IAggregate *init();

        int itemType() const
        {
            return Ac::GridSettingsItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (GridSettingsItem == itemType)
                return true;
            return DataObject::ModelItem::isTypeOfItem(itemType);
        }

        int count() const
        {
            return TotalItemCount;
        }

        int indexOf(const IModelItem *item) const
        {
            const GridSettings *a = this->a();
            if (query<IModelItem>(a->timeGridLines()) == item)
                return ItemCountOffset;
            if (query<IModelItem>(a->pitchGridLines()) == item)
                return ItemCountOffset + 1;
            if (query<IModelItem>(a->controlGridLines()) == item)
                return ItemCountOffset + 2;
            return DataObject::ModelItem::indexOf(item);
        }

        IModelItem *at(int i) const
        {
            switch (TotalItemCount - i) {
            case 0:
                return query<IModelItem>(a()->timeGridLines());
            case 1:
                return query<IModelItem>(a()->pitchGridLines());
            case 2:
                return query<IModelItem>(a()->controlGridLines());
            default:
                return DataObject::ModelItem::at(i);
            }
        }

        IModelList *findList(int listType) const
        {
            switch (listType) {
            case TimeGridLineItem:
                return query<IModelList>(a()->timeGridLines());
            case PitchGridLineItem:
                return query<IModelList>(a()->pitchGridLines());
            case ControlGridLineItem:
                return query<IModelList>(a()->controlGridLines());
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
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return DataObject::createAggregate(interfaceType);
        }
    }

    void clear()
    {
        _controlGridLines->clear();
        _pitchGridLines->clear();
        _timeGridLines->clear();
        setControlSnap(DEFAULT_GRIDSETTINGS_CONTROLSNAP);
        setPitchSnap(DEFAULT_GRIDSETTINGS_PITCHSNAP);
        setTimeSnap(DEFAULT_GRIDSETTINGS_TIMESNAP);
        setGridSnapEnabled(DEFAULT_GRIDSETTINGS_GRIDSNAPENABLED);
        setSnapEnabled(DEFAULT_GRIDSETTINGS_SNAPENABLED);
        Mi::Core::DataObject::clear();
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_GRIDSETTINGS_H




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
