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
class Parent;

class Item
{
public:
    Item()
        :   _parent(0)
        ,   _model(0)
    {}
    virtual ~Item() {}

    virtual int type() const = 0;
    virtual bool isParent() const { return false; }
    virtual bool isList() const { return false; }

    Parent *parent() const { return _parent; }

    Model *model() const { return _model; }
    virtual void setModel(Model *model) { _model = model; }
    inline QModelIndex index();

    virtual QVariant data(int role) const
    {
        Q_UNUSED(role);
        return QVariant();
    }

    void setParentAndModel(Parent *parent, Model *model)
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
    Parent *_parent;
    Model *_model;
};

template <class T> inline T *item_cast(Item *item)
{
    return int(T::Type) == int(item->type()) ? static_cast<T*>(item) : 0;
}

class Parent : public Item
{
public:
    Parent() {}
    ~Parent() {}

    bool isParent() const { return true; }

    virtual int childCount() const = 0;
    virtual Item *childAt(int i) const = 0;
    virtual int childIndex(Item *child) const = 0;

    virtual void sortChildren()
    {
        d_sortChildren();
    }

    void setModel(Model *model)
    {
        Item::setModel(model);
        for (int i = 0;  i < childCount();  ++i)
            childAt(i)->setModel(model);
    }

protected:
    virtual void d_sortChildren()
    {
        for (int i = 0;  i < childCount();  ++i) {
            Item *child = childAt(i);
            if (child && child->isParent())
                static_cast<Parent*>(child)->sortChildren();
        }
    }
};

template <class T>
class List : public Parent
{
public:
    enum { Type = ListItem };

    List() {}
    ~List() {}

    int type() const { return Type; }
    bool isList() const { return true; }

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
    GridLine() {}
    ~GridLine() {}
};

class TimeLine : public GridLine
{
public:
    enum { Type = TimeLineItem };

    TimeLine() {}
    ~TimeLine() {}

    int type() const { return Type; }
};

class PitchLine : public GridLine
{
public:
    enum { Type = PitchLineItem };

    PitchLine() {}
    ~PitchLine() {}

    int type() const { return Type; }
};

class ControlLine : public GridLine
{
public:
    enum { Type = ControlLineItem };

    ControlLine() {}
    ~ControlLine() {}

    int type() const { return Type; }
};

class Point : public Item
{
public:
    Point() {}
    ~Point() {}
};

class PitchCurvePoint : public Point
{
public:
    enum { Type = PitchCurvePointItem };

    PitchCurvePoint() {}
    ~PitchCurvePoint() {}

    int type() const { return Type; }
};

class ControlCurvePoint : public Point
{
public:
    enum { Type = ControlCurvePointItem };

    ControlCurvePoint() {}
    ~ControlCurvePoint() {}

    int type() const { return Type; }
};

class PitchCurve : public List<PitchCurvePoint>
{
public:
    enum { Type = PitchCurveItem };

    PitchCurve() {}
    ~PitchCurve() {}

    int type() const { return Type; }
};

class ControlCurve : public List<ControlCurvePoint>
{
public:
    enum { Type = ControlCurveItem };

    ControlCurve() {}
    ~ControlCurve() {}

    int type() const { return Type; }
};

class Note : public Parent
{
public:
    enum { Type = NoteItem };

    Note()
        :   _pitchCurve(new PitchCurve)
        ,   _controlCurves(new List<ControlCurve>)
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

private:
    PitchCurve *_pitchCurve;
    List<ControlCurve> *_controlCurves;
};

class Track : public List<Note>
{
public:
    enum { Type = TrackItem };

    Track() {}
    ~Track() {}

    int type() const { return Type; }
};

class GridSettings : public Parent
{
public:
    enum { Type = GridSettingsItem };

    GridSettings()
        :   _timeLines(new List<TimeLine>)
        ,   _pitchLines(new List<PitchLine>)
        ,   _controlLines(new List<ControlLine>)
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

private:
    List<TimeLine> *_timeLines;
    List<PitchLine> *_pitchLines;
    List<ControlLine> *_controlLines;
};

class Score : public Parent
{
public:
    enum { Type = GridSettingsItem };

    Score()
        :   _tracks(new List<Track>)
        ,   _gridSettings(new GridSettings)
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

class Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0)
        :   QAbstractItemModel(parent)
        ,   _score(new Score)
    {
        _score->setModel(this);
    }

    ~Model()
    {}

    Score *score() const
    {
        return _score;
    }

    QModelIndex indexFromItem(Item *item) const
    {
        if (!item)
            return QModelIndex();
        Parent *p = item->parent();
        if (!p)
            return QModelIndex();
        return createIndex(p->childIndex(item), 0, p);
    }

    Item *itemFromIndex(const QModelIndex &index) const
    {
        if ((index.row() < 0) || (index.column() < 0) || (index.model() != this))
            return 0;
        Parent *p = static_cast<Parent*>(index.internalPointer());
        if (!p)
            return 0;
        return p->childAt(index.row());
    }

    QModelIndex index(int row, int column, const QModelIndex &parent) const
    {
        Item *itm = itemFromIndex(parent);
        if (!itm || !itm->isParent())
            return QModelIndex();
        Parent *parentItem = static_cast<Parent*>(itm);
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
        Item *parentItem = static_cast<Item*>(child.internalPointer());
        return indexFromItem(parentItem);
    }

    int rowCount(const QModelIndex &parent) const
    {
        if (!parent.isValid())
            return _score->childCount();
        Item *itm = itemFromIndex(parent);
        if (!itm || !itm->isParent())
            return 0;
        Parent *parentItem = static_cast<Parent*>(itm);
        return parentItem->childCount();
    }

    int columnCount(const QModelIndex &parent) const
    {
        return 1;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        Item *itm = index.isValid() ? itemFromIndex(index) : score();
        return itm ? itm->data(role) : QVariant();

    }

private:
    Score *_score;
    QModelIndexList _persistentIndexCache;

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
        Parent::sortChildren();
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
    const QModelIndexList &persistentIndexes = _model ? _model->_persistentIndexCache : QModelIndexList();
    QModelIndexList changedPersistentIndexesFrom;
    QModelIndexList changedPersistentIndexesTo;
    QList<T*> sorted_children;
    sorted_children.reserve(_children.count());
    for (int i = 0;  i < childCount();  ++i) {
        int r = itemPairs.at(i).second;
        sorted_children[i] = item_cast<T>(childAt(r));
        if (_model) {
            QModelIndex from = _model->createIndex(r, 0, this);
            if (persistentIndexes.contains(from)) {
                QModelIndex to = _model->createIndex(i, 0, this);
                changedPersistentIndexesFrom.append(from);
                changedPersistentIndexesTo.append(to);
            }
        }
    }
    _children = sorted_children;
    if (_model)
        _model->changePersistentIndexList(changedPersistentIndexesFrom, changedPersistentIndexesTo);
    Parent::d_sortChildren();
}

#endif // AC_MODEL_H
