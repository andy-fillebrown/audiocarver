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
class MiSortedObjectList;

namespace Private {

class MiObjectListData : public MiObjectPrivate
{
public:
    QList<MiObject*> objects;

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
    friend class Private::MiObjectListPrivate;

    Q_OBJECT
    Q_DISABLE_COPY(MiObjectList)

public:
    typedef MiObject::Properties Properties;

    MiObjectList(QObject *parent = 0)
        :   MiObject(*(new Private::MiObjectListData(this)), parent)
    {}

    virtual ~MiObjectList()
    {}

signals:
    void objectsAboutToBeInserted(int start, int end);
    void objectsInserted(int start, int end);
    void objectsAboutToBeRemoved(int start, int end);
    void objectsRemoved(int start, int end);

protected:
    MiObjectList(Private::MiObjectListData &dd, QObject *parent = 0)
        :   MiObject(dd, parent)
    {}

private:
    bool isList() const
    {
        return true;
    }

    void setErased(bool erased)
    {
        Private::MiObjectListData *d = static_cast<Private::MiObjectListData*>(d_ptr);
        MiObject::setErased(erased);
        if (erased) {
            foreach (MiObject *object, d->objects)
                if (object)
                    object->erase();
        } else {
            foreach (MiObject *object, d->objects)
                if (object)
                    object->unerase();
        }
    }
};

namespace Private {

class MiObjectListPrivate : public MiObjectListData
{
    Q_DECLARE_PUBLIC(MiObjectList)

public:
    MiObjectListPrivate(MiObject *q)
        :   MiObjectListData(q)
    {}

    virtual ~MiObjectListPrivate()
    {}

    void insert(int i, MiObject* object)
    {
        beginInsert(i, i);
        insertObject(i, object);
        endInsert(i, i);
    }

    void insert(int i, const QList<MiObject*> &objects)
    {
        const int end = i + objects.count();
        beginInsert(i, end);
        int j = i - 1;
        foreach (MiObject *object, objects)
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

    void append(MiObject *object)
    {
        insert(objects.count(), object);
    }

    void append(const QList<MiObject*> &objects)
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

    void removeOne(MiObject* object)
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

    void insertObject(int i, MiObject *object)
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

    virtual void endInsert(int start, int end)
    {
        Q_Q(MiObjectList);
        q->emit objectsInserted(start, end);
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

class MiSortedObjectListPrivate : public MiObjectListPrivate
{
public:
    MiSortedObjectListPrivate(MiObject *q)
        :   MiObjectListPrivate(q)
    {}

    virtual ~MiSortedObjectListPrivate()
    {}

    inline virtual void endInsert(int start, int end);
};

} // namespace Private

class MiSortedObjectList : public MiObjectList
{
    Q_OBJECT
    Q_DISABLE_COPY(MiSortedObjectList)
    Q_DECLARE_PRIVATE(Private::MiSortedObjectList)

public:
    MiSortedObjectList(QObject *parent = 0)
        :   MiObjectList(*(new Private::MiSortedObjectListPrivate(this)), parent)
    {}

    virtual ~MiSortedObjectList()
    {}

public slots:
    virtual void sort()
    {
        Q_D(Private::MiObjectList);
        if (isSorted())
            return;
        QList<MiObject*> list = d->objects;
        d->beginRemove(0, list.count());
        d->objects.clear();
        d->endRemove(0, list.count());
        qSort(list.begin(), list.end(), lessThan);
        d->beginInsert(0, list.count());
        d->objects.append(list);
        d->endInsert(0, list.count());
    }

protected:
    MiSortedObjectList(Private::MiSortedObjectListPrivate &dd, QObject *parent = 0)
        :   MiObjectList(dd, parent)
    {}

private:
    bool isSorted() const
    {
        Q_D(const Private::MiSortedObjectList);
        const int end = d->objects.count() - 1;
        for (int i = 0;  i < end;  ++i)
            if (lessThan(d->objects[i + 1], d->objects[i]))
                return false;
        return true;
    }

    static bool lessThan(const MiObject *a, const MiObject *b)
    {
        return false;//a->lessThan(b);
    }
};

namespace Private {

inline void MiSortedObjectListPrivate::endInsert(int start, int end)
{
    MiSortedObjectList *q = static_cast<MiSortedObjectList*>(q_ptr);
    MiObjectListPrivate::endInsert(start, end);
    q->sort();
}

} // namespace Private

Q_DECLARE_METATYPE(MiObjectList*)

#endif // MI_OBJECTLIST_H
