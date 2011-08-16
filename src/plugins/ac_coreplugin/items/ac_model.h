/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#ifndef AC_MODEL_H
#define AC_MODEL_H

#include <ac_core_enums.h>
#include <ac_core_global.h>

#include <QAbstractItemModel>
#include <QVector>

class Model;

class Item
{
public:
    explicit Item(Item *parent = 0)
        :   _parent(parent)
        ,   _model(parent ? parent->model() : 0)
    {}

    virtual ~Item() {}

    virtual int type() const = 0;

    Item *parent() const { return _parent; }
    void setParent(Item *parent) { setParentAndModel(parent, parent ? parent->model() : 0); }

    virtual int childCount() const { return 0; }
    virtual Item *childAt(int i) const { Q_UNUSED(i);  return 0; }
    virtual int childIndex(Item *child) const { Q_UNUSED(child);  return -1; }
    virtual Item *findChild(ItemType type) const { Q_UNUSED(type);  return 0; }
    virtual Item *findList(ItemType listType) const { Q_UNUSED(listType);  return 0; }
    virtual void sortChildren() { d_sortChildren(); }

    Model *model() const { return _model; }

    virtual void setModel(Model *model)
    {
        if (_model == model)
            return;
        _model = model;
        for (int i = 0;  i < childCount();  ++i)
            childAt(i)->setModel(model);
    }

    inline QModelIndex index();

    virtual QVariant data(int role) const
    {
        if (ItemTypeRole == role)
            return type();
        return QVariant();
    }

    virtual bool setData(const QVariant &value, int role)
    {
        Q_UNUSED(value);
        Q_UNUSED(role);
        return false;
    }

    virtual Qt::ItemFlags flags() const
    {
        return Qt::NoItemFlags;
    }

    void setParentAndModel(Item *parent, Model *model)
    {
        _parent = parent;
        setModel(model);
    }

    virtual bool operator<(const Item &other)
    {
        Q_UNUSED(other);
        return false;
    }

protected:
    virtual void d_sortChildren()
    {
        for (int i = 0;  i < childCount();  ++i) {
            Item *child = childAt(i);
            if (child)
                child->sortChildren();
        }
    }

    Item *_parent;
    Model *_model;
};

template <class T> inline T *item_cast(Item *item)
{
    return int(T::Type) == int(item->type()) ? static_cast<T*>(item) : 0;
}

template <class T>
class List : public Item
{
public:
    enum { Type = ListItem };

    explicit List(Item *parent = 0)
        :   Item(parent)
    {}

    ~List()
    {
        qDeleteAll(_children);
    }

    int type() const { return Type; }

    int childCount() const
    {
        return _children.count();
    }

    Item *childAt(int i) const
    {
        return _children.at(i);
    }

    int childIndex(Item *child) const
    {
        return _children.indexOf(item_cast<T>(child));
    }

    void appendChild(T *child)
    {
        insertChild(childCount(), child);
    }

    void insertChild(int i, T *child)
    {
        if (!child)
            return;
        _children.insert(i, child);
        child->setParentAndModel(this, _model);
    }

    T *takeChild(int i)
    {
        T *child = childAt(i);
        removeChild(i);
        return child;
    }

    void removeChild(int i)
    {
        Item *child = childAt(i);
        if (!child)
            return;
        child->setParentAndModel(0, 0);
        _children.removeAt(i);
    }

    inline void sortChildren();

protected:
    inline void d_sortChildren();

private:
    bool isSorted()
    {
        for (int i = 1;  i < childCount();  ++i)
            if (*_children.at(i) < *_children.at(i - 1))
                return false;
        return true;
    }

    QList<T*> _children;
};

class GridLine : public Item
{
public:
    explicit GridLine(Item *parent = 0)
        :   Item(parent)
    {}

    ~GridLine() {}
};

class TimeLine : public GridLine
{
public:
    enum { Type = TimeLineItem };

    explicit TimeLine(Item *parent = 0)
        :   GridLine(parent)
    {}

    ~TimeLine() {}

    int type() const { return Type; }
};

class PitchLine : public GridLine
{
public:
    enum { Type = PitchLineItem };

    explicit PitchLine(Item *parent = 0)
        :   GridLine(parent)
    {}

    ~PitchLine() {}

    int type() const { return Type; }
};

class ControlLine : public GridLine
{
public:
    enum { Type = ControlLineItem };

    explicit ControlLine(Item *parent = 0)
        :   GridLine(parent)
    {}

    ~ControlLine() {}

    int type() const { return Type; }
};

class Point : public Item
{
public:
    explicit Point(Item *parent = 0)
        :   Item(parent)
    {}

    ~Point() {}
};

class PitchCurvePoint : public Point
{
public:
    enum { Type = PitchCurvePointItem };

    explicit PitchCurvePoint(Item *parent = 0)
        :   Point(parent)
    {}

    ~PitchCurvePoint() {}

    int type() const { return Type; }
};

class ControlCurvePoint : public Point
{
public:
    enum { Type = ControlCurvePointItem };

    explicit ControlCurvePoint(Item *parent = 0)
        :   Point(parent)
    {}

    ~ControlCurvePoint() {}

    int type() const { return Type; }
};

class PitchCurve : public List<PitchCurvePoint>
{
public:
    enum { Type = PitchCurveItem };

    explicit PitchCurve(Item *parent = 0)
        :   List<PitchCurvePoint>(parent)
    {}

    ~PitchCurve() {}

    int type() const { return Type; }
};

class ControlCurve : public List<ControlCurvePoint>
{
public:
    enum { Type = ControlCurveItem };

    explicit ControlCurve(Item *parent = 0)
        :   List<ControlCurvePoint>(parent)
    {}

    ~ControlCurve() {}

    int type() const { return Type; }
};

class Note : public Item
{
public:
    enum { Type = NoteItem };

    explicit Note(Item *parent = 0)
        :   Item(parent)
        ,   _pitchCurve(new PitchCurve(this))
        ,   _controlCurves(new List<ControlCurve>(this))
    {}

    ~Note()
    {
        delete _controlCurves;
        delete _pitchCurve;
    }

    int type() const { return Type; }
    int childCount() const { return 2; }

    Item *childAt(int i) const
    {
        switch (i) {
        case 0: return _pitchCurve;
        case 1: return _controlCurves;
        }
        return 0;
    }

    int childIndex(Item *child) const
    {
        if (_pitchCurve == child) return 0;
        if (_controlCurves == child) return 1;
        return -1;
    }

    Item *findChild(ItemType type) const
    {
        if (PitchCurveItem == type)
            return _pitchCurve;
        return 0;
    }

    Item *findList(ItemType listType) const
    {
        if (ControlCurveItem == listType)
            return _controlCurves;
        return 0;
    }

private:
    PitchCurve *_pitchCurve;
    List<ControlCurve> *_controlCurves;
};

class Track : public Item
{
public:
    enum { Type = TrackItem };

    explicit Track(Item *parent = 0)
        :   Item(parent)
        ,   _notes(new List<Note>(parent))
    {}

    ~Track()
    {
        delete _notes;
    }

    int type() const { return Type; }

    Item *childAt(int i) const
    {
        switch (i) {
        case 0: return _notes;
        }
        return 0;
    }

    int childIndex(Item *child) const
    {
        if (_notes == child) return 0;
        return -1;
    }

    Item *findList(ItemType listType) const
    {
        if (NoteItem == listType)
            return _notes;
        return 0;
    }

private:
    List<Note> *_notes;
};

class GridSettings : public Item
{
public:
    enum { Type = GridSettingsItem };

    explicit GridSettings(Item *parent = 0)
        :   Item(parent)
        ,   _timeLines(new List<TimeLine>(this))
        ,   _pitchLines(new List<PitchLine>(this))
        ,   _controlLines(new List<ControlLine>(this))
    {}

    ~GridSettings()
    {
        delete _controlLines;
        delete _pitchLines;
        delete _timeLines;
    }

    int type() const { return Type; }
    int childCount() const { return 3; }

    Item *childAt(int i) const
    {
        switch (i) {
        case 0: return _timeLines;
        case 1: return _pitchLines;
        case 2: return _controlLines;
        }
        return 0;
    }

    int childIndex(Item *child) const
    {
        if (_timeLines == child) return 0;
        if (_pitchLines == child) return 1;
        if (_controlLines == child) return 2;
        return -1;
    }

    Item *findList(ItemType listType) const
    {
        switch (listType) {
        case TimeLineItem: return _timeLines;
        case PitchLineItem: return _pitchLines;
        case ControlLineItem: return _controlLines;
        default: return 0;
        }
    }

private:
    List<TimeLine> *_timeLines;
    List<PitchLine> *_pitchLines;
    List<ControlLine> *_controlLines;
};

class Score : public Item
{
public:
    enum { Type = GridSettingsItem };

    Score()
        :   _tracks(new List<Track>(this))
        ,   _gridSettings(new GridSettings(this))
    {}

    ~Score()
    {
        delete _gridSettings;
        delete _tracks;
    }

    int type() const { return Type; }
    int childCount() const { return 2; }

    Item *childAt(int i) const
    {
        switch(i) {
        case 0: return _tracks;
        case 1: return _gridSettings;
        }
        return 0;
    }

    int childIndex(Item *child) const
    {
        if (_tracks == child) return 0;
        if (_gridSettings == child) return 1;
        return -1;
    }

    Item *findChild(ItemType type) const
    {
        if (GridSettingsItem == type)
            return _gridSettings;
        return 0;
    }

    Item *findList(ItemType listType) const
    {
        if (TrackItem == listType)
            return _tracks;
        return 0;
    }

    Track *trackAt(int i) const
    {
        return item_cast<Track>(_tracks->childAt(i));
    }

    void appendTrack(Track *track)
    {
        _tracks->appendChild(track);
    }

    void insertTrack(int i, Track *track)
    {
        _tracks->insertChild(i, track);
    }

    Track *takeTrack(int i)
    {
        Track *track = trackAt(i);
        removeTrack(i);
        return track;
    }

    void removeTrack(int i)
    {
        _tracks->removeChild(i);
    }

    void removeTrack(Track *track)
    {
        _tracks->removeChild(childIndex(track));
    }

private:
    List<Track> *_tracks;
    GridSettings *_gridSettings;
};

class AbstractModel : public QAbstractItemModel
{
public:
    QModelIndex childIndex(ItemType type, const QModelIndex &parent) const
    {
        Item *parentItem = itemFromIndex(parent);
        return parentItem ? indexFromItem(parentItem->findChild(type)) : QModelIndex();
    }

    QModelIndex listIndex(ItemType listType, const QModelIndex &parent) const
    {
        Item *parentItem = itemFromIndex(parent);
        return parentItem ? indexFromItem(parentItem->findList(listType)) : QModelIndex();
    }

    QModelIndex index(int row, int column, const QModelIndex &parent) const
    {
        Item *parentItem = itemFromIndex(parent);
        if (!parentItem
                || row < 0
                || column < 0
                || parentItem->childCount() <= row
                || 1 <= column)
            return QModelIndex();
        return createIndex(row, column, parentItem);
    }

    QModelIndex parent(const QModelIndex &child) const
    {
        if (child.row() < 0 || child.column() < 0 || child.model() != this)
            return QModelIndex();
        return indexFromItem(static_cast<Item*>(child.internalPointer()));
    }

    int rowCount(const QModelIndex &parent) const
    {
        if (!parent.isValid())
            return _score->childCount();
        Item *parentItem = itemFromIndex(parent);
        return parentItem ? parentItem->childCount() : 0;
    }

    int columnCount(const QModelIndex &parent) const
    {
        return 1;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        Item *itm = index.isValid() ? itemFromIndex(index) : _score;
        return itm ? itm->data(role) : QVariant();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
    {
        Item *itm = index.isValid() ? itemFromIndex(index) : _score;
        return itm ? itm->setData(value, role) : false;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        Item *itm = index.isValid() ? itemFromIndex(index) : _score;
        return itm ? itm->flags() : Qt::NoItemFlags;
    }

protected:
    AbstractModel(QObject *parent)
        :   QAbstractItemModel(parent)
        ,   _score(new Score)
    {}

    QModelIndex indexFromItem(Item *item) const
    {
        if (!item)
            return QModelIndex();
        Item *parentItem = item->parent();
        if (!parentItem)
            return QModelIndex();
        return createIndex(parentItem->childIndex(item), 0, parentItem);
    }

    Item *itemFromIndex(const QModelIndex &index) const
    {
        if ((index.row() < 0) || (index.column() < 0) || (index.model() != this))
            return 0;
        Item *parentItem = static_cast<Item*>(index.internalPointer());
        if (!parentItem)
            return 0;
        return parentItem->childAt(index.row());
    }

    Score *_score;
};

class Model : public AbstractModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0)
        :   AbstractModel(parent)
    {
        _score->setModel(this);
    }

    ~Model()
    {}

    Score *score() const
    {
        return _score;
    }

private:
    QModelIndexList _persistentIndexCache;

    friend class Item;
    friend class List<ControlCurve>;
    friend class List<ControlCurvePoint>;
    friend class List<ControlLine>;
    friend class List<Note>;
    friend class List<PitchCurvePoint>;
    friend class List<PitchLine>;
    friend class List<Point>;
    friend class List<TimeLine>;
    friend class List<Track>;
};

inline QModelIndex Item::index()
{
    return _model ? _model->indexFromItem(this) : QModelIndex();
}

class ItemModelLessThan
{
public:
    ItemModelLessThan() {}

    bool operator()(const QPair<Item*, int> &l, const QPair<Item*, int> &r) const
    {
        return *(l.first) < *(r.first);
    }
};

template <class T> inline void List<T>::sortChildren()
{
    if (isSorted()) {
        Item::sortChildren();
        return;
    }
    if (_model) {
        _model->_persistentIndexCache = _model->persistentIndexList();
        emit _model->layoutAboutToBeChanged();
    }
    d_sortChildren();
    if (_model)
        emit _model->layoutChanged();
}

template <class T> inline void List<T>::d_sortChildren()
{
    QVector<QPair<Item*, int> > itemPairs(childCount());
    for (int i = 0;  i < childCount(); ++i)
        itemPairs.append(QPair<Item*, int>(childAt(i), i));
    ItemModelLessThan lt;
    qStableSort(itemPairs.begin(), itemPairs.end(), lt);
    const QModelIndexList &indexes = _model ? _model->_persistentIndexCache : QModelIndexList();
    QModelIndexList oldIndexes, newIndexes;
    QList<T*> sorted_children;
    sorted_children.reserve(_children.count());
    for (int i = 0;  i < childCount();  ++i) {
        int r = itemPairs.at(i).second;
        sorted_children[i] = item_cast<T>(childAt(r));
        if (_model) {
            QModelIndex oldIndex = _model->createIndex(r, 0, this);
            if (indexes.contains(oldIndex)) {
                QModelIndex newIndex = _model->createIndex(i, 0, this);
                oldIndexes.append(oldIndex);
                newIndexes.append(newIndex);
            }
        }
    }
    _children = sorted_children;
    if (_model)
        _model->changePersistentIndexList(oldIndexes, newIndexes);
    Item::d_sortChildren();
}

#endif // AC_MODEL_H
