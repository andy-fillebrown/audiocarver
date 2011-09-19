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

#ifndef ACOBJECTLIST_H
#define ACOBJECTLIST_H

#include <acobject.h>

#include <QVariant>

template <class T> class ObjectList;

template <class T> inline void qDeleteAll(ObjectList<T> *list);

template <class T> class ObjectListPrivate : public ObjectPrivate
{
public:
    QList<T*> objects;

    inline ObjectListPrivate(ObjectList<T> *q);

    const T &t() const
    {
        static T t;
        return t;
    }
};

template <class T> class ObjectList : public Object
{
public:
    explicit ObjectList(QObject *parent = 0)
        :   Object(*(new ObjectListPrivate<T>(this)), parent)
    {
        Q_D_TEMPLATE(ObjectList);
        setObjectName(QString("%1s").arg(d->t().objectName()));
    }

    int count() const
    {
        Q_D_TEMPLATE(const ObjectList);
        return d->objects.count();
    }

    bool isEmpty() const
    {
        return count() == 0;
    }

    T *at(int i) const
    {
        Q_D_TEMPLATE(const ObjectList);
        return d->objects.at(i);
    }

    int indexOf(T *object, int from = 0)
    {
        Q_D_TEMPLATE(ObjectList);
        return d->objects.indexOf(object, from);
    }

    void append(T *object)
    {
        insert(count(), object);
    }

    void insert(int i, T *object)
    {
        Q_D_TEMPLATE(ObjectList);
        if (d->objects.contains(object))
            return;
        object->setParent(this);
        d->beginInsertObjects(i, i);
        d->objects.insert(i, object);
        d->endInsertObjects();
    }

    void removeAt(int i)
    {
        Q_D_TEMPLATE(ObjectList);
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
        Q_D_TEMPLATE(ObjectList);
        d->beginRemoveObjects(0, count() - 1);
        d->objects.clear();
        d->endRemoveObjects();
    }

    // IModelItem

    Ac::ItemType type() const
    {
        return Ac::ListItem;
    }

    int modelItemCount() const
    {
        return count();
    }

    int modelItemIndex(IModelItem *item) const
    {
        Q_D_TEMPLATE(const ObjectList);
        return d->objects.indexOf(item->query<T>());
    }

    IModelItem *modelItemAt(int i) const
    {
        return at(i);
    }

    QVariant data(int role) const
    {
        if (Ac::ListTypeRole == role) {
            Q_D_TEMPLATE(const ObjectList);
            return d->t().type();
        }
        return Object::data(role);
    }

private:
    Q_DISABLE_COPY(ObjectList)
    Q_DECLARE_PRIVATE_TEMPLATE(ObjectList)

    friend void qDeleteAll<T>(ObjectList<T>*);
};

template <class T> inline
ObjectListPrivate<T>::ObjectListPrivate(ObjectList<T> *q)
    :   ObjectPrivate(q)
{}

template <class T> inline
void qDeleteAll(ObjectList<T> *list)
{
    if (!list)
        return;
    foreach (T *object, list->d_func()->objects)
        delete object;
}

#endif // ACOBJECTLIST_H
