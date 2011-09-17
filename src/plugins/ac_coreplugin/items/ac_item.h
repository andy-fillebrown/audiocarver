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

#include <ac_core_global.h>
#include <ac_coreenums.h>
#include <ac_point.h>

#include <QColor>

#include <QObject>
#include <QVariant>
#include <QVector>

class Object;
class Model;
class Note;
template <class T> class ObjectList;
class Score;
class ScoreObject;
class Track;

class AC_CORE_EXPORT ObjectPrivate
{
public:
    Object *q;
    Model *model;

    ObjectPrivate(Object *q)
        :   q(q)
        ,   model(0)
    {}

    virtual ~ObjectPrivate() {}

    void setModel(Model *model);
    void beginInsertObjects(int first, int last);
    void endInsertObjects();
    void beginRemoveObjects(int first, int last);
    void endRemoveObjects();
};

class AC_CORE_EXPORT Object : public QObject
{
    Q_OBJECT

public:
    ~Object()
    {
        delete d_ptr;
    }

    virtual ItemType type() const = 0;

    Object *parent() const
    {
        return qobject_cast<Object*>(QObject::parent());
    }

    virtual void setParent(Object *parent)
    {
        QObject::setParent(parent);
        d_ptr->setModel(parent ? parent->model() : 0);
    }

    Model *model() const
    {
        return d_ptr->model;
    }

    virtual int componentCount() const
    {
        return 0;
    }

    virtual int componentIndex(Object *component) const
    {
        Q_UNUSED(component);
        Q_ASSERT(false);
        return -1;
    }

    virtual Object *componentAt(int i) const
    {
        Q_UNUSED(i);
        return 0;
    }

    virtual Object *findComponent(ItemType type) const
    {
        Q_UNUSED(type);
        return 0;
    }

    virtual Object *findComponentList(ItemType type) const
    {
        Q_UNUSED(type);
        return 0;
    }

    virtual QVariant data(int role) const
    {
        switch (role) {
        case Qt::DisplayRole:
            return objectName();
        case ItemTypeRole:
            return type();
        default:
            return QVariant();
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

protected:
    Object(ObjectPrivate &dd, QObject *parent = 0)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

    ObjectPrivate *d_ptr;

private:
    Q_DISABLE_COPY(Object)
    Q_DECLARE_PRIVATE(Object)
};

template <class T> class ObjectListPrivate : public ObjectPrivate
{
public:
    QList<T*> objects;

    ObjectListPrivate(ObjectList<T> *q)
        :   ObjectPrivate(q)
    {}
};

template <class T> class ObjectList : public Object
{
public:
    explicit ObjectList(QObject *parent = 0)
        :   Object(*(new ObjectListPrivate<T>(this)), parent)
    {
        static T t;
        setObjectName(QString("%1s").arg(t.objectName()));
    }

    ItemType type() const
    {
        return ListItem;
    }

    int count() const
    {
        ObjectListPrivate<T> *d = reinterpret_cast<ObjectListPrivate<T>*>(d_ptr);
        return d->objects.count();
    }

    T *at(int i) const
    {
        ObjectListPrivate<T> *d = reinterpret_cast<ObjectListPrivate<T>*>(d_ptr);
        return d->objects.at(i);
    }

    int indexOf(T *object, int from = 0)
    {
        ObjectListPrivate<T> *d = reinterpret_cast<ObjectListPrivate<T>*>(d_ptr);
        return d->objects.indexOf(object, from);
    }

    void append(T *object)
    {
        insert(count(), object);
    }

    void insert(int i, T *object)
    {
        ObjectListPrivate<T> *d = reinterpret_cast<ObjectListPrivate<T>*>(d_ptr);
        if (d->objects.contains(object))
            return;
        object->setParent(this);
        d->beginInsertObjects(i, i);
        d->objects.insert(i, object);
        d->endInsertObjects();
    }

    void removeAt(int i)
    {
        ObjectListPrivate<T> *d = reinterpret_cast<ObjectListPrivate<T>*>(d_ptr);
        d->beginRemoveObjects(i, i);
        d->objects.removeAt(i);
        d->endRemoveObjects();
    }

    int componentCount() const
    {
        return count();
    }

    int componentIndex(Object *component) const
    {
        ObjectListPrivate<T> *d = reinterpret_cast<ObjectListPrivate<T>*>(d_ptr);
        return d->objects.indexOf(qobject_cast<T*>(component));
    }

    Object *componentAt(int i) const
    {
        return at(i);
    }

    QVariant data(int role) const
    {
        static T t;
        if (ListTypeRole == role)
            return t.type();
        return Object::data(role);
    }
};

class CurvePrivate;
class AC_CORE_EXPORT Curve : public Object
{
    Q_OBJECT
    Q_PROPERTY(PointList points READ points WRITE setPoints)

public:
    const PointList &points() const;
    virtual void setPoints(const PointList &points);

    ScoreObject *parent() const;

    // IModelItem

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

protected:
    Curve(CurvePrivate &dd, QObject *parent = 0);

private:
    Q_DISABLE_COPY(Curve)
    Q_DECLARE_PRIVATE(Curve)
};

class PitchCurvePrivate;
class AC_CORE_EXPORT PitchCurve : public Curve
{
    Q_OBJECT

public:
    explicit PitchCurve(QObject *parent = 0);

    ItemType type() const
    {
        return PitchCurveItem;
    }

    void setPoints(const PointList &points);

private:
    Q_DISABLE_COPY(PitchCurve)
    Q_DECLARE_PRIVATE(PitchCurve)
};

class ControlCurvePrivate;
class AC_CORE_EXPORT ControlCurve : public Curve
{
    Q_OBJECT
    Q_PROPERTY(int controlId READ controlId WRITE setControlId)

public:
    explicit ControlCurve(QObject *parent = 0);

    ItemType type() const
    {
        return ControlCurveItem;
    }

    int controlId() const;
    void setControlId(int controlId);

    void setPoints(const PointList &points);

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(ControlCurve)
    Q_DECLARE_PRIVATE(ControlCurve)
};

class ScoreObjectPrivate;
class AC_CORE_EXPORT ScoreObject : public Object
{
    Q_OBJECT
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)

public:
    enum {
        ComponentCount = 2
    };

    virtual qreal length() const = 0;

    qreal volume() const;
    void setVolume(qreal volume);

    ScoreObject *parent() const
    {
        return qobject_cast<ScoreObject*>(QObject::parent());
    }

    PitchCurve *pitchCurve() const;
    ObjectList<ControlCurve> *controlCurves() const;

    int componentCount() const
    {
        return ComponentCount;
    }

    int componentIndex(Object *component) const;
    Object *componentAt(int i) const;
    Object *findComponent(ItemType type) const;
    Object *findComponentList(ItemType type) const;
    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

protected:
    ScoreObject(ScoreObjectPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(ScoreObject)
    Q_DECLARE_PRIVATE(ScoreObject)
};

class NotePrivate;
class AC_CORE_EXPORT Note : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)

public:
    explicit Note(QObject *parent = 0);

    ItemType type() const
    {
        return NoteItem;
    }

    qreal length() const;
    void setLength(qreal length);

    Track *parent() const;

    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(Note)
    Q_DECLARE_PRIVATE(Note)
};

class TrackPrivate;
class AC_CORE_EXPORT Track : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QString instrument READ instrument WRITE setInstrument)

public:
    enum {
        ComponentCount = ScoreObject::ComponentCount + 1
    };

    explicit Track(QObject *parent = 0);

    ItemType type() const
    {
        return TrackItem;
    }

    qreal length() const;

    const QColor &color() const;
    void setColor(const QColor &color);

    const QString &instrument() const;
    void setInstrument(const QString &instrument);

    Score *parent() const;

    ObjectList<Note> *notes() const;

    int componentCount() const
    {
        return ComponentCount;
    }

    int componentIndex(Object *component) const;
    Object *componentAt(int i) const;
    Object *findComponentList(ItemType type) const;
    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(Track)
    Q_DECLARE_PRIVATE(Track)
};

class ScorePrivate;
class AC_CORE_EXPORT Score : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)

public:
    enum {
        ComponentCount = ScoreObject::ComponentCount + 1
    };

    explicit Score(QObject *parent = 0);

    ItemType type() const
    {
        return ScoreItem;
    }

    qreal length() const;
    void setLength(qreal length);

    ObjectList<Track> *tracks() const;

    void setModel(Model *model);

    int componentCount() const
    {
        return ComponentCount;
    }

    int componentIndex(Object *component) const;
    Object *componentAt(int i) const;
    Object *findComponentList(ItemType type) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(Score)
    Q_DECLARE_PRIVATE(Score)
};

#endif // AC_ITEM_H
