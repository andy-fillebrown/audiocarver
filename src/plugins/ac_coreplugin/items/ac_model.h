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

#include <QColor>

#include <QAbstractItemModel>
#include <QPointF>
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
    virtual const char *className() const = 0;

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
        switch (role) {
        case ItemTypeRole: return type();
        case Qt::DisplayRole: return className();
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

    const char *className() const
    {
        static T t;
        static QString name = QString("%1s").arg(t.className());
        return qPrintable(name);
    }

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

    inline void insertChild(int i, T *child);

    T *takeChild(int i)
    {
        T *child = childAt(i);
        removeChild(i);
        return child;
    }

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
    {}

    ~TimeLine() {}

    int type() const { return Type; }
    const char *className() const { return "TimeLine"; }
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
    const char *className() const { return "PitchLine"; }
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
    const char *className() const { return "ControlLine"; }
};

class Point : public Item
{
public:
    explicit Point(Item *parent = 0)
        :   Item(parent)
    {}

    ~Point() {}

    QVariant data(int role) const
    {
        if (PointRole == role)
            return _pos;
        return Item::data(role);
    }

    bool setData(const QVariant &value, int role)
    {
        if (PointRole == role) {
            setPos(value.toPointF());
            return true;
        }
        return Item::setData(value, role);
    }

    const QPointF &pos() const { return _pos; }
    virtual void setPos(QPointF pos)
    {
        if (pos.x() < 0.0f)
            pos.setX(0.0f);
        if (pos.y() < 0.0f)
            pos.setY(0.0f);
        if (_pos == pos)
            return;
        beginDataChange();
        _pos = pos;
        endDataChange();
    }

private:
    QPointF _pos;
};

class PitchPoint : public Point
{
public:
    enum { Type = PitchPointItem };

    explicit PitchPoint(Item *parent = 0)
        :   Point(parent)
    {}

    ~PitchPoint() {}

    int type() const { return Type; }
    const char *className() const { return "PitchPoint"; }

    void setPos(QPointF pos)
    {
        if (127.0f < pos.y())
            pos.setY(127.0f);
        Point::setPos(pos);
    }
};

class CurvePoint : public Point
{
public:
    explicit CurvePoint(Item *parent = 0)
        :   Point(parent)
        ,   _curveType(NoCurve)
        ,   _stretchType(NoStretch)
    {}

    ~CurvePoint() {}

    QVariant data(int role) const
    {
        switch (role) {
        case CurveTypeRole: return _curveType;
        case StretchTypeRole: return _stretchType;
        default: return Point::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case CurveTypeRole: setCurveType(CurveType(value.toInt())); return true;
        case StretchTypeRole: setStretchType(StretchType(value.toInt())); return true;
        default: return Point::setData(value, role);
        }
    }

    virtual void setPos(QPointF pos)
    {
        if (1.0f < pos.x())
            pos.setX(1.0f);
        Point::setPos(pos);
    }

    CurveType curveType() const { return _curveType; }
    void setCurveType(CurveType type)
    {
        if (_curveType == type)
            return;
        beginDataChange();
        _curveType = type;
        endDataChange();
    }

    StretchType stretchType() const { return _stretchType; }
    void setStretchType(StretchType type)
    {
        if (_stretchType == type)
            return;
        beginDataChange();
        _stretchType = type;
        endDataChange();
    }

private:
    CurveType _curveType;
    StretchType _stretchType;
};


class PitchCurvePoint : public CurvePoint
{
public:
    enum { Type = PitchCurvePointItem };

    explicit PitchCurvePoint(Item *parent = 0)
        :   CurvePoint(parent)
    {}

    ~PitchCurvePoint() {}

    int type() const { return Type; }
    const char *className() const { return "PitchCurvePoint"; }

    void setPos(QPointF pos)
    {
        if (127.0f < pos.y())
            pos.setY(127.0f);
        CurvePoint::setPos(pos);
    }
};

class ControlCurvePoint : public CurvePoint
{
public:
    enum { Type = ControlCurvePointItem };

    explicit ControlCurvePoint(Item *parent = 0)
        :   CurvePoint(parent)
    {}

    ~ControlCurvePoint() {}

    int type() const { return Type; }
    const char *className() const { return "ControlCurvePoint"; }

    void setPos(QPointF pos)
    {
        if (1.0f < pos.y())
            pos.setY(1.0f);
        CurvePoint::setPos(pos);
    }
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
    const char *className() const { return "PitchCurve"; }
};

class ControlCurve : public List<ControlCurvePoint>
{
public:
    enum { Type = ControlCurveItem };

    explicit ControlCurve(Item *parent = 0)
        :   List<ControlCurvePoint>(parent)
        ,   _controlIndex(0)
    {}

    ~ControlCurve() {}

    int type() const { return Type; }
    const char *className() const { return "ControlCurve"; }

    QVariant data(int role) const
    {
        switch (role) {
        case ControlIndexRole: return _controlIndex;
        default: return List<ControlCurvePoint>::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case ControlIndexRole: setControlIndex(value.toInt()); return true;
        default: return false;
        }
    }

    int controlIndex() const { return _controlIndex; }
    void setControlIndex(int index)
    {
        if (_controlIndex == index)
            return;
        beginDataChange();
        _controlIndex = index;
        endDataChange();
    }

private:
    int _controlIndex;
};

class Note : public Item
{
public:
    enum { Type = NoteItem };

    explicit Note(Item *parent = 0)
        :   Item(parent)
        ,   _pitchCurve(new PitchCurve(this))
        ,   _controlCurves(new List<ControlCurve>(this))
        ,   _origin(new PitchPoint(this))
        ,   _length(0.0f)
        ,   _height(0.0f)
        ,   _volume(0.9f)
    {}

    ~Note()
    {
        delete _controlCurves;
        delete _pitchCurve;
    }

    int type() const { return Type; }
    const char *className() const { return "Note"; }

    int childCount() const { return 3; }

    Item *childAt(int i) const
    {
        switch (i) {
        case 0: return _pitchCurve;
        case 1: return _controlCurves;
        case 2: return _origin;
        default: return 0;
        }
    }

    int childIndex(Item *child) const
    {
        if (_pitchCurve == child) return 0;
        if (_controlCurves == child) return 1;
        if (_origin == child) return 2;
        return -1;
    }

    Item *findChild(ItemType type) const
    {
        switch (type) {
        case PitchCurveItem: return _pitchCurve;
        case PitchPointItem: return _origin;
        default: return 0;
        }
    }

    Item *findList(ItemType listType) const
    {
        if (ControlCurveItem == listType)
            return _controlCurves;
        return 0;
    }

    QVariant data(int role) const
    {
        switch (role) {
        case PointRole: return _origin->pos();
        case LengthRole: return _length;
        case HeightRole: return _height;
        case VolumeRole: return _volume;
        default: return Item::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case PointRole: _origin->setPos(value.toPointF()); return true;
        case LengthRole: setLength(value.toReal()); return true;
        case HeightRole: setHeight(value.toReal()); return true;
        case VolumeRole: setVolume(value.toReal()); return true;
        default: return false;
        }
    }

    PitchCurve *pitchCurve() const { return _pitchCurve; }
    List<ControlCurve> *controlCurves() const { return _controlCurves; }
    PitchPoint *origin() const { return _origin; }

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

    qreal height() const { return _height; }
    void setHeight(qreal height)
    {
        if (_height == height)
            return;
        beginDataChange();
        _height = height;
        endDataChange();
    }

    qreal volume() const { return _volume; }
    void setVolume(qreal volume)
    {
        if (volume < 0.0f)
            volume = 0.0f;
        if (1.0f < volume)
            volume = 1.0f;
        if (_volume == volume)
            return;
        beginDataChange();
        _volume = volume;
        endDataChange();
    }

private:
    PitchCurve *_pitchCurve;
    List<ControlCurve> *_controlCurves;
    PitchPoint *_origin;
    qreal _length;
    qreal _height;
    qreal _volume;
};

class Track : public Item
{
public:
    enum { Type = TrackItem };

    explicit Track(Item *parent = 0)
        :   Item(parent)
        ,   _notes(new List<Note>(parent))
        ,   _volume(0.9f)
        ,   _color(Qt::red)
    {}

    ~Track()
    {
        delete _notes;
    }

    int type() const { return Type; }
    const char *className() const { return "Track"; }

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

    QVariant data(int role) const
    {
        switch (role) {
        case InstrumentRole: return _instrument;
        case VolumeRole: return _volume;
        case ColorRole: return _color;
        default: return Item::data(role);
        }
    }

    bool setData(const QVariant &value, int role)
    {
        switch (role) {
        case InstrumentRole: setInstrument(value.toString()); return true;
        case VolumeRole: setVolume(value.toReal()); return true;
        case ColorRole: setColor(value.value<QColor>()); return true;
        default: return false;
        }
    }

    const QString &instrument() const { return _instrument; }
    void setInstrument(const QString &instrument)
    {
        if (_instrument == instrument)
            return;
        beginDataChange();
        _instrument = instrument;
        endDataChange();
    }

    qreal volume() const { return _volume; }
    void setVolume(qreal volume)
    {
        if (volume < 0.0f)
            volume = 0.0f;
        if (1.0f < volume)
            volume = 1.0f;
        if (_volume == volume)
            return;
        beginDataChange();
        _volume = volume;
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
    List<Note> *_notes;
    QString _instrument;
    qreal _volume;
    QColor _color;
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
    const char *className() const { return "GridSettings"; }

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

    List<TimeLine> *timeLines() const { return _timeLines; }
    List<PitchLine> *pitchLines() const { return _pitchLines; }
    List<ControlLine> *controlLines() const { return _controlLines; }

private:
    List<TimeLine> *_timeLines;
    List<PitchLine> *_pitchLines;
    List<ControlLine> *_controlLines;
};

class Score : public Item
{
public:
    enum { Type = ScoreItem };

    Score()
        :   _tracks(new List<Track>(this))
        ,   _gridSettings(new GridSettings(this))
        ,   _volume(1.0f)
    {}

    ~Score()
    {
        delete _gridSettings;
        delete _tracks;
    }

    int type() const { return Type; }
    const char *className() const { return "Score"; }

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
        default: return false;
        }
    }

    List<Track> *tracks() const { return _tracks; }
    GridSettings *gridSettings() const { return _gridSettings; }

    qreal volume() const { return _volume; }
    void setVolume(qreal volume)
    {
        if (volume < 0.0f)
            volume = 0.0f;
        if (1.0f < volume)
            volume = 1.0f;
        if (_volume == volume)
            return;
        beginDataChange();
        _volume = volume;
        endDataChange();
    }

private:
    List<Track> *_tracks;
    GridSettings *_gridSettings;
    qreal _volume;
};

class AbstractItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ~AbstractItemModel() {}

    virtual QModelIndex childIndex(ItemType type, const QModelIndex &parent) const = 0;
    virtual QModelIndex listIndex(ItemType listType, const QModelIndex &parent) const = 0;

signals:
    void dataAboutToChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

protected:
    AbstractItemModel(QObject *parent)
        :   QAbstractItemModel(parent)
    {}
};

class Model : public AbstractItemModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0)
        :   AbstractItemModel(parent)
        ,   _score(new Score)
    {
        _score->setModel(this);
    }

    ~Model()
    {
        delete _score;
    }

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

    Score *score() const
    {
        return _score;
    }

protected:
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

private:
    Score *_score;
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

template <class T> inline void List<T>::insertChild(int i, T *child)
{
    if (!child || _children.contains(child))
        return;
    if (_model)
        _model->beginInsertRows(index(), i, i);
    _children.insert(i, child);
    child->setParentAndModel(this, _model);
    if (_model)
        _model->endInsertRows();
}

template <class T> inline void List<T>::removeChild(int i)
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
