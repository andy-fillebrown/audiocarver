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

#ifndef MI_OBJECT_H
#define MI_OBJECT_H

#include <mi_core_global.h>
#include <QDebug>
#include <QMetaProperty>
#include <QMetaType>
#include <QObject>

class Object : protected QObject
{
    Q_OBJECT

public:
    virtual bool addChild(Object *child)
    {
        if (!children().contains(child)) {
            child->setParent(this);
            return true;
        }
        return false;
    }

    int propertyCount() const
    {
        return metaObject()->propertyCount();
    }

    const char *propertyName(int i) const
    {
        return metaObject()->property(i).name();
    }

    QVariant propertyValue(int i) const
    {
        return metaObject()->property(i).read(this);
    }

    // Note that the shorter form of connect() doesn't work.
    bool connect(const Object *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType type = Qt::UniqueConnection) const
    {
        return QObject::connect(sender, signal, receiver, member, type);
    }

    // Use this instead of qobject_cast<T*>(object)
    template <typename T>
    static T* cast(QObject* object)
    {
#       if !defined(QT_NO_MEMBER_TEMPLATES) && !defined(QT_NO_QOBJECT_CHECK)
            reinterpret_cast<T*>(0)->qt_check_for_QOBJECT_macro(*reinterpret_cast<T*>(object));
#       endif
        return static_cast<T*>(reinterpret_cast<T*>(0)->staticMetaObject.cast(object));
    }

protected:
    template <typename T>
    const QList<T*> &childrenAs() const
    {
        return reinterpret_cast<const QList<T*>&>(children());
    }

    template <typename T>
    QList<T*> &childrenAs()
    {
        return const_cast<QList<T*>&>(reinterpret_cast<const QList<T*>&>(children()));
    }
};

Q_DECLARE_METATYPE(Object*);

class Child : public Object
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)

    int _value;

public:
    Child()
        :   _value(3)
    {}

    int value() const
    {
        return _value;
    }

    void setValue(int value)
    {
        _value = value;
    }

    void change()
    {
        emit changed();
    }

    virtual bool lessThan(const Child *other) const
    {
        Q_UNUSED(other);
        return false;
    }

signals:
    void changed();
};

class Parent : public Object
{
    Q_OBJECT

public:
    const QList<Child*> &children() const
    {
        return childrenAs<Child>();
    }

    virtual bool addChild(Object *child)
    {
        Child *c = cast<Child>(child);
        if (!c)
            return false;
        if (Object::addChild(child)) {
            sortChildren();
            // Note that the shorter form of connect() doesn't work.
            return c->connect(c, SIGNAL(changed()), this, SLOT(childChanged()));
        }
        return false;
    }

public slots:
    void childChanged()
    {
        qDebug() << "child changed!";
    }

private:
    void sortChildren()
    {
        QList<Child*> &c = childrenAs<Child>();
        qSort(c.begin(), c.end(), lessThan);
    }

    static bool lessThan(const Child *a, const Child *b)
    {
        return a->lessThan(b);
    }
};

class ChildB : public Child
{
    Q_OBJECT
};

class ParentB : public Parent
{
    Q_OBJECT

public:
    const QList<ChildB*> &children() const
    {
        return childrenAs<ChildB>();
    }
};

class MiDatabase;
class MiObject;
class MiSortedObjectList;

namespace Private {

class MiObjectPrivate
{
public:
    MiObject *q_ptr;
    bool erased;

    MiObjectPrivate(MiObject *q)
        :   q_ptr(q)
        ,   erased(false)
    {}

    virtual ~MiObjectPrivate()
    {}
};

} // namespace Private

class MI_CORE_EXPORT MiObject : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiObject)

public:
    enum Properties {
        PropertyOffset = 1,
        PropertyCount = PropertyOffset
    };

    explicit MiObject(QObject *parent = 0)
        :   QObject(parent)
        ,   d_ptr(new Private::MiObjectPrivate(this))
    {}

    virtual ~MiObject()
    {
        delete d_ptr;
    }

    MiDatabase *database() const;

    virtual bool isDatabase() const
    {
        return false;
    }

    virtual bool isList() const
    {
        return false;
    }

    bool isErased() const
    {
        return d_ptr->erased;
    }

    void erase()
    {
        if (isErased())
            return;
        emit aboutToBeErased();
        setErased(true);
        emit erased();
    }

    void unerase()
    {
        if (!isErased())
            return;
        emit aboutToBeUnerased();
        setErased(false);
        emit unerased();
    }

signals:
    void aboutToBeErased();
    void erased();
    void aboutToBeUnerased();
    void unerased();

protected:
    MiObject(Private::MiObjectPrivate &dd, QObject *parent)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

    virtual void setErased(bool erased)
    {
        d_ptr->erased = erased;
    }

    void beginChangeProperty(int propertyIndex);
    virtual void endChangeProperty(int propertyIndex);

    Private::MiObjectPrivate *d_ptr;
};

Q_DECLARE_METATYPE(MiObject*);

class MI_CORE_EXPORT MiSortedObject : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiSortedObject)

public:
    typedef MiObject::Properties Properties;

    virtual ~MiSortedObject()
    {}

    void setList(MiSortedObjectList *list)
    {}

    virtual bool lessThan(const MiSortedObject *other) const
    {
        Q_UNUSED(other);
        return false;
    }

protected:
    MiSortedObject(Private::MiObjectPrivate &dd, QObject *parent)
        :   MiObject(dd, parent)
    {}

    void sortList() const;
};

#endif // MI_OBJECT_H
