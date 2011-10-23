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

#ifndef AC_OBJECTLIST_H
#define AC_OBJECTLIST_H

#include <ac_object.h>

#include <QVariant>

class ObjectList;
class ObjectListPrivate : public ObjectPrivate
{
public:
    inline ObjectListPrivate(ObjectList *q);
};

class ObjectList : public Object
{
    Q_OBJECT

public:
    virtual void append(Object *object) = 0;
    virtual void insert(int i, Object *object) = 0;
    virtual void remove(Object *object) = 0;

protected:
    ObjectList(ObjectListPrivate &dd, QObject *parent = 0)
        :   Object(dd, parent)
    {}
};

inline ObjectListPrivate::ObjectListPrivate(ObjectList *q)
    :   ObjectPrivate(q)
{}

template <class T> class ObjectTList;

template <class T> inline void qDeleteAll(ObjectTList<T> *list);

template <class T> class ObjectTListPrivate : public ObjectListPrivate
{
public:
    QList<T*> objects;

    inline ObjectTListPrivate(ObjectTList<T> *q);

    const T &t() const
    {
        static T t;
        return t;
    }
};

template <class T> class ObjectTList : public ObjectList
{
public:
    explicit ObjectTList(QObject *parent = 0)
        :   ObjectList(*(new ObjectTListPrivate<T>(this)), parent)
    {
        Q_TD(ObjectTList);
        setObjectName(QString("%1s").arg(d->t().objectName()));
    }

    int count() const
    {
        Q_TD(const ObjectTList);
        return d->objects.count();
    }

    bool isEmpty() const
    {
        return count() == 0;
    }

    T *at(int i) const
    {
        Q_TD(const ObjectTList);
        return d->objects.at(i);
    }

    int indexOf(T *object, int from = 0)
    {
        Q_TD(ObjectTList);
        return d->objects.indexOf(object, from);
    }

    void append(T *object)
    {
        insert(count(), object);
    }

    void insert(int i, T *object)
    {
        Q_TD(ObjectTList);
        if (d->objects.contains(object))
            return;
        object->setParent(this);
        d->beginInsertObjects(i, i);
        d->objects.insert(i, object);
        d->endInsertObjects();
    }

    void removeAt(int i)
    {
        Q_TD(ObjectTList);
        Object *object = d->objects[i];
        d->beginRemoveObjects(i, i);
        d->objects.removeAt(i);
        d->endRemoveObjects();
        object->setParent(0);
    }

    void clear()
    {
        if (isEmpty())
            return;
        Q_TD(ObjectTList);
        d->beginRemoveObjects(0, count() - 1);
        d->objects.clear();
        d->endRemoveObjects();
    }

    // ObjectList
    void append(Object *object)
    {
        T *t = qobject_cast<T*>(object);
        if (t)
            append(t);
    }

    void insert(int i, Object *object)
    {
        T *t = qobject_cast<T*>(object);
        if (t)
            insert(i, t);
    }

    void remove(Object *object)
    {
        int i = indexOf(qobject_cast<T*>(object));
        if (0 <= i && i < count())
            removeAt(i);
    }

    // IModelItem
    int type() const
    {
        return Ac::ListItem;
    }

    int persistentRoleCount() const
    {
        return 0;
    }

    int modelItemCount() const
    {
        return count();
    }

    int modelItemIndex(IModelItem *item) const
    {
        Q_TD(const ObjectTList);
        int n = d->objects.count();
        for (int i = 0;  i < n;  ++i)
            if (item == d->objects.at(i)->query(Ac::ModelItemInterface))
                return i;
        return -1;
    }

    IModelItem *modelItemAt(int i) const
    {
        return at(i);
    }

    QVariant data(int role) const
    {
        if (Ac::ListTypeRole == role) {
            Q_TD(const ObjectTList);
            return d->t().type();
        }
        return Object::data(role);
    }

private:
    Q_DISABLE_COPY(ObjectTList)
    Q_DECLARE_TEMPLATE_PRIVATE(ObjectTList)

    friend void qDeleteAll<T>(ObjectTList<T>*);
};

template <class T> inline
ObjectTListPrivate<T>::ObjectTListPrivate(ObjectTList<T> *q)
    :   ObjectListPrivate(q)
{}

template <class T> inline
void qDeleteAll(ObjectTList<T> *list)
{
    if (!list)
        return;
    foreach (T *object, list->d_func()->objects)
        delete object;
}

#endif // AC_OBJECTLIST_H
