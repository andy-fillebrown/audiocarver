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

#ifndef MI_OBJECTLIST_H
#define MI_OBJECTLIST_H

#include <mi_object.h>

class MiObjectList;

namespace Private {

class MiObjectListData : public MiObjectPrivate
{
public:
    QList<MiListObject*> objects;

    MiObjectListData(MiObject *q)
        :   MiObjectPrivate(q)
    {}

    virtual ~MiObjectListData()
    {}
};

class MiObjectListPrivate;

} // namespace Private

class MI_CORE_EXPORT MiObjectList : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiObjectList)

public:
    typedef MiObject::Properties Properties;

    virtual ~MiObjectList()
    {}

public slots:
    virtual void sort()
    {
        if (isSorted())
            return;
        QList<MiListObject*> list = d->objects;
        emit objectsAboutToBeRemoved(0, list.count());
        d->objects.clear();
        emit objectsRemoved(0, list.count());
        qSort(list.begin(), list.end(), lessThan);
        emit objectsAboutToBeInserted(0, list.count());
        d->objects.append(list);
        emit objectsInserted(0, list.count());
    }

signals:
    void objectsAboutToBeInserted(int start, int end);
    void objectsInserted(int start, int end);
    void objectsAboutToBeRemoved(int start, int end);
    void objectsRemoved(int start, int end);

protected:
    MiObjectList(Private::MiObjectListData &dd, QObject *parent = 0)
        :   MiObject(dd, parent)
        ,   d(&dd)
    {}

private:
    bool isList() const
    {
        return true;
    }

    void setErased(bool erased)
    {
        MiObject::setErased(erased);
        if (erased) {
            foreach (MiListObject *object, d->objects)
                if (object)
                    object->erase();
        } else {
            foreach (MiListObject *object, d->objects)
                if (object)
                    object->unerase();
        }
    }

    bool isSorted() const
    {
        const int end = d->objects.count() - 1;
        for (int i = 0;  i < end;  ++i)
            if (lessThan(d->objects[i + 1], d->objects[i]))
                return false;
        return true;
    }

    static bool lessThan(const MiListObject *a, const MiListObject *b)
    {
        return a->lessThan(b);
    }

    friend class MiFiler;
    friend class Private::MiObjectListPrivate;
    Private::MiObjectListData *d;
};

namespace Private {

class MiObjectListPrivate : public MiObjectListData
{
    Q_DECLARE_PUBLIC(MiObjectList)

public:
    void insert(int i, MiListObject* object)
    {
        beginInsert(i, i);
        insertObject(i, object);
        endInsert(i, i);
    }

    void insert(int i, const QList<MiListObject*> &objects)
    {
        const int end = i + objects.count();
        beginInsert(i, end);
        int j = i - 1;
        foreach (MiListObject *object, objects)
            insertObject(++j, object);
        endInsert(i, end);
    }

    template <typename T>
    void insert(int i, const QList<T*> &objects)
    {
        const int end = i + objects.count();
        beginInsert(i, end);
        int j = i - 1;
        foreach (T *object, objects)
            insertObject(++j, object);
        endInsert(i, end);
    }

    void append(MiListObject *object)
    {
        insert(objects.count(), object);
    }

    void append(const QList<MiListObject*> &objects)
    {
        insert(objects.count(), objects);
    }

    template <typename T>
    void append(const QList<T*> &objects)
    {
        insert<T>(objects.count(), objects);
    }

    void removeAt(int i)
    {
        beginRemove(i, i);
        objects.removeAt(i);
        endRemove(i, i);
    }

    void removeAt(int i, int count)
    {
        const int end = i + count - 1;
        beginRemove(i, end);
        for (int j = i;  j <= end;  ++j)
            objects.removeAt(j);
        endRemove(i, end);
    }

    void removeOne(MiListObject* object)
    {
        removeAt(objects.indexOf(object));
    }

    void clear()
    {
        removeAt(0, objects.count());
    }

    template <typename T>
    const QList<T*> &cast() const
    {
#ifdef QT_DEBUG
        foreach (MiObject *object, objects)
            Q_ASSERT(qobject_cast<T*>(object));
        return reinterpret_cast<const QList<T*>&>(objects);
#else
        return reinterpret_cast<const QList<T*>&>(objects);
#endif
    }

private:
    void insertObject(int i, MiListObject *object)
    {
        Q_Q(MiObject);
        objects.insert(i, object);
        if (q != object->parent())
            object->setParent(q);
    }

    void beginInsert(int start, int end)
    {
        Q_Q(MiObjectList);
        q->emit objectsAboutToBeInserted(start, end);
    }

    void endInsert(int start, int end)
    {
        Q_Q(MiObjectList);
        q->emit objectsInserted(start, end);
        q->sort();
    }

    void beginRemove(int start, int end)
    {
        Q_Q(MiObjectList);
        q->emit objectsAboutToBeRemoved(start, end);
    }

    void endRemove(int start, int end)
    {
        Q_Q(MiObjectList);
        q->emit objectsRemoved(start, end);
    }
};

} // namespace Private

Q_DECLARE_METATYPE(MiObjectList*)

#endif // MI_OBJECTLIST_H
