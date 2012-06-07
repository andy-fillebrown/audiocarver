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

#ifndef AC_TRACK_H
#define AC_TRACK_H

#include "ac_database_scoreobject.h"

namespace Database {

class AC_CORE_EXPORT Track : public ScoreObject
{
    friend class ObjectFactory;

    enum { RoleCount = 4 };
    enum { ItemCount = 1 };

    int _color;
    QString _instrument;
    int _visible : 1;
    int _recording : 1;

    IAggregator *_notes;

protected:
    enum {
        RoleCountOffset = Object::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount,
        ItemCountOffset = Object::TotalItemCount,
        TotalItemCount = ItemCountOffset + ItemCount
    };

    Track()
        :   _color(Ac::red)
        ,   _visible(false)
        ,   _recording(false)
        ,   _notes(0)
    {}

    IAggregator *init();
    ~Track();

    int color() const
    {
        return _color;
    }

    bool setColor(int color);

    QString instrument() const
    {
        return _instrument;
    }

    bool setInstrument(const QString &instrument);

    bool isVisible() const
    {
        return _visible;
    }

    bool setVisible(bool visible);

    bool isRecording() const
    {
        return _recording;
    }

    bool setRecording(bool recording);

    IAggregator *notes() const
    {
        return _notes;
    }

    class AC_CORE_EXPORT ModelData : public ScoreObject::ModelData
    {
        Track *a() const
        {
            return cast<Track>(Object::ModelData::a());
        }

    public:
        ModelData(Track *aggregator)
            :   ScoreObject::ModelData(aggregator)
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
                return Ac::ColorRole;
            case 1:
                return Ac::InstrumentRole;
            case 2:
                return Ac::VisibilityRole;
            case 3:
                return Ac::RecordingRole;
            default:
                return ScoreObject::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Ac::ColorRole:
                return a()->color();
            case Ac::InstrumentRole:
                return a()->instrument();
            case Ac::VisibilityRole:
                return a()->isVisible();
            case Ac::RecordingRole:
                return a()->isRecording();
            default:
                return ScoreObject::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Ac::ColorRole:
                return a()->setColor(qvariant_cast<int>(data));
            case Ac::InstrumentRole:
                return a()->setInstrument(qvariant_cast<QString>(data));
            case Ac::VisibilityRole:
                return a()->setVisible(qvariant_cast<bool>(data));
            case Ac::RecordingRole:
                return a()->setRecording(qvariant_cast<bool>(data));
            default:
                return ScoreObject::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public ScoreObject::ModelItem
    {
        Track *a() const
        {
            return cast<Track>(Object::ModelItem::a());
        }

    public:
        ModelItem(Track *aggregator)
            :   ScoreObject::ModelItem(aggregator)
        {}

        IAggregate *init();

    protected:
        // IModelItem
        int itemType() const
        {
            return Ac::TrackItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (Ac::TrackItem == itemType)
                return true;
            return ScoreObject::ModelItem::isTypeOfItem(itemType);
        }

        int count() const
        {
            return TotalItemCount;
        }

        int indexOf(const IModelItem *item) const
        {
            const Track *a = this->a();
            if (query<IModelItem>(a->notes()) == item)
                return ItemCountOffset;
            return ScoreObject::ModelItem::indexOf(item);
        }

        IModelItem *at(int i) const
        {
            Q_ASSERT(0 <= (TotalItemCount - i));
            switch (TotalItemCount - i) {
            case 0:
                return query<IModelItem>(a()->notes());
            default:
                return ScoreObject::ModelItem::at(i);
            }
        }

        IModelList *findList(int listType) const
        {
            switch (listType) {
            case Ac::NoteItem:
                return query<IModelList>(a()->notes());
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

} // namespace Database

//class Note;
//class Score;

//class TrackPrivate;
//class AC_CORE_EXPORT Track : public ScoreObject
//{
//    Q_OBJECT
//    Q_PROPERTY(QColor color READ color WRITE setColor)
//    Q_PROPERTY(QString instrument READ instrument WRITE setInstrument)
//    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
//    Q_PROPERTY(bool recording READ isRecording WRITE setRecording)

//public:
//    enum { Type = Ac::TrackItem };
//    enum { ModelItemCount = ScoreObject::ModelItemCount + 1 };

//    Track(QObject *parent = 0);

//    Score *score() const;
//    ObjectTList<Note> *notes() const;

//    void setZValue(qreal z);

//    // Properties
//    const QColor &color() const;
//    void setColor(const QColor &color);
//    const QString &instrument() const;
//    void setInstrument(const QString &instrument);
//    bool isVisible() const;
//    void setVisible(bool visible);
//    bool isRecording() const;
//    void setRecording(bool recording);

//    // ScoreObject
//    qreal length() const;

//    // Object
//    QString name() const { return objectName(); }

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
//            return Ac::ColorRole;
//        case 1:
//            return Ac::InstrumentRole;
//        case 2:
//            return Ac::VisibilityRole;
//        case 3:
//            return Ac::RecordingRole;
//        default:
//            return ScoreObject::persistentRoleAt(i);
//        }
//    }

//    QVariant data(int role) const;
//    bool setData(const QVariant &value, int role);

//private:
//    Q_DECLARE_PRIVATE(Track)

//    friend class NotePrivate;
//};

//class TrackPrivate : public ScoreObjectPrivate
//{
//    Q_DECLARE_PUBLIC(Track)

//public:
//    QColor color;
//    QString instrument;
//    ObjectTList<Note> *notes;
//    int recording : 32;

//    TrackPrivate(Track *q);
//    void init();
//    ~TrackPrivate();

//    GraphicsParentPrivate *graphicsParent() const;
//};

#endif // AC_TRACK_H
