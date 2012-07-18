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

#ifndef AC_CORE_SCORE_H
#define AC_CORE_SCORE_H

#include "ac_core_scoreobject.h"

namespace Ac {
namespace Core {

class AC_CORE_EXPORT Score : public ScoreObject
{
    friend class DataObjectFactory;

    enum { RoleCount = 2 };
    enum { ItemCount = 7 };

    qreal _length;
    qreal _startTime;

    IAggregator *_tracks;
    IAggregator *_timeGridLines;
    IAggregator *_pitchGridLines;
    IAggregator *_controlGridLines;
    IAggregator *_gridSettings;
    IAggregator *_projectSettings;
    IAggregator *_viewSettings;

public:
    static Score *instance();

protected:
    enum {
        RoleCountOffset = DataObject::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount,
        ItemCountOffset = DataObject::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    Score()
        :   _length(60.0f)
        ,   _startTime(0.0f)
        ,   _tracks(0)
        ,   _timeGridLines(0)
        ,   _pitchGridLines(0)
        ,   _controlGridLines(0)
        ,   _gridSettings(0)
        ,   _projectSettings(0)
        ,   _viewSettings(0)
    {}

    IAggregator *init();
    ~Score();

    qreal length() const
    {
        return _length;
    }

    bool setLength(qreal length);

    qreal startTime() const
    {
        return _startTime;
    }

    bool setStartTime(qreal time);

    IAggregator *tracks() const
    {
        return _tracks;
    }

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

    IAggregator *gridSettings() const
    {
        return _gridSettings;
    }

    IAggregator *projectSettings() const
    {
        return _projectSettings;
    }

    IAggregator *viewSettings() const
    {
        return _viewSettings;
    }

    class AC_CORE_EXPORT ModelData : public ScoreObject::ModelData
    {
        friend class Score;

        Score *a() const
        {
            return static_cast<Score*>(DataObject::ModelData::a());
        }

    protected:
        ModelData(Score *aggregator)
            :   ScoreObject::ModelData(aggregator)
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
                return Ac::LengthRole;
            case 1:
                return Ac::StartTimeRole;
            default:
                return ScoreObject::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::LengthRole:
                return a()->length();
            case Ac::StartTimeRole:
                return a()->startTime();
            default:
                return ScoreObject::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::LengthRole:
                return a()->setLength(qvariant_cast<qreal>(data));
            case Ac::StartTimeRole:
                return a()->setStartTime(qvariant_cast<qreal>(data));
            default:
                return ScoreObject::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public ScoreObject::ModelItem
    {
        friend class Score;

        Score *a() const
        {
            return static_cast<Score*>(DataObject::ModelItem::a());
        }

    protected:
        ModelItem(Score *aggregator)
            :   ScoreObject::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        int itemType() const
        {
            return Ac::ScoreItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (Ac::ScoreItem == itemType)
                return true;
            return ScoreObject::ModelItem::isTypeOfItem(itemType);
        }

        int count() const
        {
            return TotalItemCount;
        }

        int indexOf(const IModelItem *item) const
        {
            const Score *a = this->a();
            if (query<IModelItem>(a->tracks()) == item)
                return ItemCountOffset;
            if (query<IModelItem>(a->timeGridLines()) == item)
                return ItemCountOffset + 1;
            if (query<IModelItem>(a->pitchGridLines()) == item)
                return ItemCountOffset + 2;
            if (query<IModelItem>(a->controlGridLines()) == item)
                return ItemCountOffset + 3;
            if (query<IModelItem>(a->gridSettings()) == item)
                return ItemCountOffset + 4;
            if (query<IModelItem>(a->projectSettings()) == item)
                return ItemCountOffset + 5;
            if (query<IModelItem>(a->viewSettings()) == item)
                return ItemCountOffset + 6;
            return ScoreObject::ModelItem::indexOf(item);
        }

        IModelItem *at(int i) const
        {
            switch (TotalItemCount - i) {
            case 0:
                return query<IModelItem>(a()->tracks());
            case 1:
                return query<IModelItem>(a()->timeGridLines());
            case 2:
                return query<IModelItem>(a()->pitchGridLines());
            case 3:
                return query<IModelItem>(a()->controlGridLines());
            case 4:
                return query<IModelItem>(a()->gridSettings());
            case 5:
                return query<IModelItem>(a()->projectSettings());
            case 6:
                return query<IModelItem>(a()->viewSettings());
            default:
                return ScoreObject::ModelItem::at(i);
            }
        }

        IModelItem *findItem(int itemType) const
        {
            switch (itemType) {
            case Ac::GridSettingsItem:
                return query<IModelItem>(a()->gridSettings());
            case Ac::ProjectSettingsItem:
                return query<IModelItem>(a()->projectSettings());
            case Ac::ViewSettingsItem:
                return query<IModelItem>(a()->viewSettings());
            default:
                return ScoreObject::ModelItem::findItem(itemType);
            }
        }

        IModelList *findList(int listType) const
        {
            switch (listType) {
            case Ac::TrackItem:
                return query<IModelList>(a()->tracks());
            case Ac::TimeGridLineItem:
                return query<IModelList>(a()->timeGridLines());
            case Ac::PitchGridLineItem:
                return query<IModelList>(a()->pitchGridLines());
            case Ac::ControlGridLineItem:
                return query<IModelList>(a()->controlGridLines());
            default:
                return ScoreObject::ModelItem::findList(listType);
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
            return ScoreObject::createAggregate(interfaceType);
        }
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_SCORE_H




//#ifndef AC_SCORE_H
//#define AC_SCORE_H

//#include <ac_scoreobject.h>

//class GridSettings;
//class IPlayCursor;
//class ProjectSettings;
//class Track;
//class ViewSettings;

//class QGraphicsLineItem;

//class QTimer;

//class Score;
//class ScorePrivate : public ScoreObjectPrivate
//{
//public:
//    qreal length;
//    qreal startTime;
//    qreal playCursorTime;
//    ObjectTList<Track> *tracks;
//    GridSettings *gridSettings;
//    ViewSettings *viewSettings;
//    ProjectSettings *projectSettings;
//    IPlayCursor *playCursorImplementation;
//    QGraphicsLineItem *timeLabelPlayCursor;
//    QGraphicsLineItem *pitchPlayCursor;
//    QGraphicsLineItem *controlPlayCursor;
//    QTimer *playCursorTimer;

//    ScorePrivate(Score *q);
//    void init();
//    ~ScorePrivate();

//    void updateGraphicsParent() {}
//    void updateLength();
//    void setPlayCursorTime(qreal time);
//};

//class AC_CORE_EXPORT Score //: public ScoreObject
//{
//    Q_OBJECT
//    Q_PROPERTY(qreal length READ length WRITE setLength)
//    Q_PROPERTY(qreal startTime READ startTime WRITE setStartTime)

//public:
//    enum { Type = Ac::ScoreItem };
//    enum { ModelItemCount = ScoreObject::ModelItemCount + 4 };

//    explicit Score(QObject *parent = 0);

//    static Score *instance();

//    ObjectTList<Track> *tracks() const;
//    GridSettings *gridSettings() const;
//    ViewSettings *viewSettings() const;
//    ProjectSettings *projectSettings() const;

//    QGraphicsItem *sceneItem(int type) const;

//    void clear();

    // Properties
//    qreal length() const;
//    void setLength(qreal length);
//    qreal startTime() const;
//    void setStartTime(qreal time);

//    qreal playCursorTime() const;
//    void setPlaybackTime(qreal time);
//    void highlightPlayCursor();
//    void unhighlightPlayCursor();

//    // IModelItem
//    int type() const { return Type; }
//    int modelItemCount() const { return ModelItemCount; }
//    int modelItemIndex(const IModelItem *item) const;
//    IModelItem *modelItemAt(int i) const;
//    IModelItem *findModelItem(int type) const;
//    IModelItem *findModelItemList(int type) const;

//    int persistentRoleAt(int i) const
//    {
//        switch (i - staticMetaObject.propertyOffset()) {
//        case 0:
//            return Ac::LengthRole;
//        case 1:
//            return Ac::StartTimeRole;
//        default:
//            return ScoreObject::persistentRoleAt(i);
//        }
//    }

//    QVariant data(int role) const;
//    bool setData(const QVariant &value, int role);

//signals:
//    void aboutToBeReset();
//    void reset();

//private slots:
//    void updatePlayCursor();

//private:
//    Q_DECLARE_PRIVATE(Score)

//    friend class GridSettingsPrivate;
//    friend class TrackPrivate;
//};

//#endif // AC_SCORE_H
