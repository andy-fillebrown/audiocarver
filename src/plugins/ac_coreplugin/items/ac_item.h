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

#ifndef AC_ITEM_H
#define AC_ITEM_H

#include <ac_coreenums.h>
#include <ac_point.h>

#include <QColor>

#include <QModelIndex>
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
    virtual QString className() const = 0;

    Item *parent() const { return _parent; }
    void setParent(Item *parent)
    {
        setParentAndModel(parent, parent ? parent->model() : 0);
    }

    virtual int childCount() const { return 0; }
    virtual Item *childAt(int i) const { Q_UNUSED(i);  return 0; }
    virtual int childIndex(Item *child) const { Q_UNUSED(child);  return -1; }
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
        switch (role) {
        case ItemTypeRole: return type();
        case Qt::DisplayRole: return _objectName;
        default: return QVariant();
        }
    }

    virtual bool setData(const QVariant &value, int role)
    {
        Q_UNUSED(value);
        Q_UNUSED(role);
        return false;
    }

    virtual Qt::ItemFlags flags() const
    {
        return Qt::ItemIsSelectable
                | Qt::ItemIsEditable
                | Qt::ItemIsEnabled;
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

    inline void beginDataChange();
    inline void endDataChange();

    Item *_parent;
    Model *_model;
    QString _objectName;
};

template <class T> inline T *item_cast(Item *item)
{
    return int(T::Type) == int(item->type()) ? static_cast<T*>(item) : 0;
}

template <class T>
class ItemList : public Item
{
public:
    enum { Type = ListItem };

    explicit ItemList(Item *parent = 0)
        :   Item(parent)
    {
        _objectName = className();
    }

    ~ItemList()
    {
        qDeleteAll(_children);
    }

    int type() const { return Type; }

    QString className() const
    {
        static T t;
        return QString("%1s").arg(t.className());
    }

    int childCount() const { return _children.count(); }
    Item *childAt(int i) const { return _children.at(i); }

    int childIndex(Item *child) const
    {
        return _children.indexOf(item_cast<T>(child));
    }

    void appendChild(T *child)
    {
        insertChild(childCount(), child);
    }

    inline virtual void insertChild(int i, T *child);

    inline void removeChild(int i);
    inline void sortChildren();

    QVariant data(int role) const
    {
        if (ListTypeRole == role)
            return T::Type;
        return Item::data(role);
    }

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

class AudibleItem : public Item
{
public:
    explicit AudibleItem(Item *parent = 0)
        :   Item(parent)
        ,   _volume(1.0f)
    {}

    ~AudibleItem() {}

    QVariant data(int role) const
    {
        switch (role) {
        case VolumeRole: return _volume;
        default: return Item::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case VolumeRole: setVolume(value.toReal()); return true;
        default: return Item::setData(value, role);
        }
    }

    qreal volume() const { return _volume; }
    void setVolume(qreal volume)
    {
        volume = qBound(qreal(0.0f), volume, qreal(1.0f));
        if (_volume == volume)
            return;
        beginDataChange();
        _volume = volume;
        endDataChange();
    }

private:
    qreal _volume;
};

class Note : public AudibleItem
{
public:
    enum { Type = NoteItem };

    explicit Note(Item *parent = 0)
        :   AudibleItem(parent)
    {
        _points.append(Point());
        _objectName = className();
    }

    ~Note() {}

    int type() const { return Type; }
    QString className() const { return "Note"; }

    QVariant data(int role) const
    {
        switch (role) {
        case PointsRole: return QVariant::fromValue(_points);
        default: return AudibleItem::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case PointsRole: setPoints(value.value<PointList>()); return true;
        default: return AudibleItem::setData(value, role);
        }
    }

    const PointList &points() const { return _points; }
    void setPoints(const PointList &points)
    {
        if (_points == points)
            return;
        beginDataChange();
        _points = points;
        conformPoints();
        endDataChange();
    }

    bool operator<(const Item &other)
    {
        Q_ASSERT(NoteItem == other.type());
        const Note &b = static_cast<const Note&>(other);
        if (points()[0] < b.points()[0])
            return true;
        return false;
    }

private:
    PointList _points;

    void conformPoints()
    {
        qStableSort(_points);
        for (int i = 0;  i < _points.count();  ++i) {
            QPointF &pos = _points[i].pos;
            pos.setX(qMax(qreal(0.0f), pos.x()));
            pos.setY(qBound(qreal(0.0f), pos.y(), qreal(127.0f)));
        }
    }
};

class Track : public AudibleItem
{
public:
    enum { Type = TrackItem };

    explicit Track(Item *parent = 0)
        :   AudibleItem(parent)
        ,   _notes(new ItemList<Note>(this))
        ,   _color(Qt::red)
    {
        _objectName = className();
    }

    ~Track()
    {
        delete _notes;
    }

    int type() const { return Type; }
    QString className() const { return "Track"; }

    int childCount() const { return 1; }

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

    QVariant data(int role) const
    {
        switch (role) {
        case InstrumentRole: return _instrument;
        case ColorRole: return _color;
        default: return AudibleItem::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case InstrumentRole: setInstrument(value.toString()); return true;
        case ColorRole: setColor(value.value<QColor>()); return true;
        default: return AudibleItem::setData(value, role);
        }
    }

    ItemList<Note> *notes() const { return _notes; }

    const QString &instrument() const { return _instrument; }
    void setInstrument(const QString &instrument)
    {
        if (_instrument == instrument)
            return;
        beginDataChange();
        _instrument = instrument;
        endDataChange();
    }

    const QColor &color() const { return _color; }
    void setColor(const QColor &color)
    {
        if (_color == color)
            return;
        beginDataChange();
        _color = color;
        endDataChange();
    }

private:
    ItemList<Note> *_notes;
    QString _instrument;
    QColor _color;
};

class GridLine : public Item
{
public:
    explicit GridLine(Item *parent = 0)
        :   Item(parent)
        ,   _location(0.0f)
        ,   _priority(0)
        ,   _color(Qt::lightGray)
    {}

    ~GridLine() {}

    QVariant data(int role) const
    {
        switch (role) {
        case LocationRole: return _location;
        case PriorityRole: return _priority;
        case ColorRole: return _color;
        case LabelRole: return _label;
        default: return Item::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case LocationRole: setLocation(value.toReal()); return true;
        case PriorityRole: setPriority(value.toInt()); return true;
        case ColorRole: setColor(value.value<QColor>()); return true;
        case LabelRole: setLabel(value.toString()); return true;
        default: return Item::setData(value, role);
        }
    }

    qreal location() const { return _location; }
    void setLocation(qreal location)
    {
        if (location < 0.0f)
            location = 0.0f;
        if (_location == location)
            return;
        beginDataChange();
        _location = location;
        endDataChange();
    }

    int priority() const { return _priority; }
    void setPriority(int priority)
    {
        if (_priority == priority)
            return;
        beginDataChange();
        _priority = priority;
        endDataChange();
    }

    const QColor &color() const { return _color; }
    void setColor(const QColor &color)
    {
        if (_color == color)
            return;
        beginDataChange();
        _color = color;
        endDataChange();
    }

    const QString &label() const { return _label; }
    void setLabel(const QString &label)
    {
        if (_label == label)
            return;
        beginDataChange();
        _label = label;
        endDataChange();
    }

private:
    qreal _location;
    int _priority;
    QColor _color;
    QString _label;
};

class TimeLine : public GridLine
{
public:
    enum { Type = TimeLineItem };

    explicit TimeLine(Item *parent = 0)
        :   GridLine(parent)
    {
        _objectName = className();
    }

    ~TimeLine() {}

    int type() const { return Type; }
    QString className() const { return "TimeLine"; }
};

class PitchLine : public GridLine
{
public:
    enum { Type = PitchLineItem };

    explicit PitchLine(Item *parent = 0)
        :   GridLine(parent)
    {
        _objectName = className();
    }

    ~PitchLine() {}

    int type() const { return Type; }
    QString className() const { return "PitchLine"; }
};

class ControlLine : public GridLine
{
public:
    enum { Type = ControlLineItem };

    explicit ControlLine(Item *parent = 0)
        :   GridLine(parent)
    {
        _objectName = className();
    }

    ~ControlLine() {}

    int type() const { return Type; }
    QString className() const { return "ControlLine"; }
};

class GridSettings : public Item
{
public:
    enum { Type = GridSettingsItem };

    explicit GridSettings(Item *parent = 0)
        :   Item(parent)
        ,   _timeLines(new ItemList<TimeLine>(this))
        ,   _pitchLines(new ItemList<PitchLine>(this))
        ,   _controlLines(new ItemList<ControlLine>(this))
    {
        _objectName = className();
    }

    ~GridSettings()
    {
        delete _controlLines;
        delete _pitchLines;
        delete _timeLines;
    }

    int type() const { return Type; }
    QString className() const { return "GridSettings"; }

    int childCount() const { return 3; }

    Item *childAt(int i) const
    {
        switch (i) {
        case 0: return _timeLines;
        case 1: return _pitchLines;
        case 2: return _controlLines;
        default: return 0;
        }
    }

    int childIndex(Item *child) const
    {
        if (_timeLines == child) return 0;
        if (_pitchLines == child) return 1;
        if (_controlLines == child) return 2;
        return -1;
    }

    ItemList<TimeLine> *timeLines() const { return _timeLines; }
    ItemList<PitchLine> *pitchLines() const { return _pitchLines; }
    ItemList<ControlLine> *controlLines() const { return _controlLines; }

private:
    ItemList<TimeLine> *_timeLines;
    ItemList<PitchLine> *_pitchLines;
    ItemList<ControlLine> *_controlLines;
};

class Score : public AudibleItem
{
public:
    enum { Type = ScoreItem };

    Score()
        :   _tracks(new ItemList<Track>(this))
        ,   _gridSettings(new GridSettings(this))
        ,   _length(120.0f)
    {
        _objectName = className();
    }

    ~Score()
    {
        delete _gridSettings;
        delete _tracks;
    }

    int type() const { return Type; }
    QString className() const { return "Score"; }

    int childCount() const { return 2; }

    Item *childAt(int i) const
    {
        switch(i) {
        case 0: return _tracks;
        case 1: return _gridSettings;
        default: return 0;
        }
    }

    int childIndex(Item *child) const
    {
        if (_tracks == child) return 0;
        if (_gridSettings == child) return 1;
        return -1;
    }

    QVariant data(int role) const
    {
        switch (role) {
        case LengthRole: return _length;
        default: return AudibleItem::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case LengthRole: setLength(value.toReal()); return true;
        default: return AudibleItem::setData(value, role);
        }
    }

    ItemList<Track> *tracks() const { return _tracks; }
    GridSettings *gridSettings() const { return _gridSettings; }

    qreal length() const { return _length; }
    void setLength(qreal length)
    {
        if (length < 0.0f)
            length = 0.0f;
        if (_length == length)
            return;
        beginDataChange();
        _length = length;
        endDataChange();
    }

private:
    ItemList<Track> *_tracks;
    GridSettings *_gridSettings;
    qreal _length;
};

#include <ac_model.h>

inline QModelIndex Item::index()
{
    return _model ? _model->indexFromItem(this) : QModelIndex();
}

inline void Item::beginDataChange()
{
    if (_model)
        emit _model->dataAboutToChange(index(), index());
}

inline void Item::endDataChange()
{
    if (_model)
        emit _model->dataChanged(index(), index());
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

template <class T> inline void ItemList<T>::insertChild(int i, T *child)
{
    if (!child || _children.contains(child))
        return;
    child->setParentAndModel(this, _model);
    if (_model)
        _model->beginInsertRows(index(), i, i);
    _children.insert(i, child);
    if (_model)
        _model->endInsertRows();
}

template <class T> inline void ItemList<T>::removeChild(int i)
{
    Item *child = childAt(i);
    if (!child || !_children.contains(item_cast<T>(child)))
        return;
    if (_model)
        _model->beginRemoveRows(index(), i, i);
    child->setParentAndModel(0, 0);
    _children.removeAt(i);
    if (_model)
        _model->endRemoveRows();
}

template <class T> inline void ItemList<T>::sortChildren()
{
    if (isSorted())
        return;
    if (_model) {
        _model->_persistentIndexCache = _model->persistentIndexList();
        _model->maybeEmitLayoutAboutToBeChanged();
    }
    d_sortChildren();
}

template <class T> inline void ItemList<T>::d_sortChildren()
{
    const int count = childCount();
    QVector<QPair<Item*, int> > itemPairs(count);
    for (int i = 0;  i < count;  ++i)
        itemPairs[i] = QPair<Item*, int>(childAt(i), i);
    ItemModelLessThan lt;
    qStableSort(itemPairs.begin(), itemPairs.end(), lt);
    const QModelIndexList &indexes = _model ? _model->_persistentIndexCache : QModelIndexList();
    QModelIndexList oldIndexes, newIndexes;
    QList<T*> sorted_children;
    sorted_children.reserve(count);
    for (int i = 0;  i < count;  ++i) {
        int r = itemPairs.at(i).second;
        sorted_children.append(item_cast<T>(childAt(r)));
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

#endif // AC_ITEM_H
