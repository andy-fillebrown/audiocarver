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
    QList<QObject*> objects;

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
    Q_DECLARE_PRIVATE(Private::MiObjectList)

public:
    typedef MiObject::Properties Properties;

    virtual ~MiObjectList()
    {}

public slots:
    virtual void sort()
    {}

signals:
    void objectsAboutToBeInserted(int start, int end);
    void objectsInserted(int start, int end);
    void objectsAboutToBeMoved(int start, int end, int destination);
    void objectsMoved(int start, int end, int destination);
    void objectsAboutToBeRemoved(int start, int end);
    void objectsRemoved(int start, int end);

protected:
    MiObjectList(QObject *parent)
        :   MiObject(*(new Private::MiObjectListData(this)), parent)
    {}
};

namespace Private {

class MiObjectListPrivate : public MiObjectListData
{
    Q_DECLARE_PUBLIC(MiObjectList)

public:
    void insert(int i, QObject *object)
    {
        Q_Q(MiObjectList);
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

    void beginMove(int start, int end, int destination)
    {
        Q_Q(MiObjectList);
        q->emit objectsAboutToBeMoved(start, end, destination);
    }

    void endMove(int start, int end, int destination)
    {
        Q_Q(MiObjectList);
        q->emit objectsMoved(start, end, destination);
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
        q->sort();
    }
};

} // namespace Private

template <typename T>
class MiList : public MiObjectList
{
    Q_DISABLE_COPY(MiList)
    Q_DECLARE_PRIVATE(Private::MiObjectList)

public:
    typedef MiObjectList::Properties Properties;

    explicit MiList(QObject *parent = 0)
        :   MiObjectList(parent)
    {}

    virtual ~MiList()
    {}

    bool isEmpty() const
    {
        Q_D(const Private::MiObjectList);
        return d->objects.isEmpty();
    }

    int count() const
    {
        Q_D(const Private::MiObjectList);
        return d->objects.count();
    }

    T *at(int i) const
    {
        Q_D(const Private::MiObjectList);
        return qobject_cast<T*>(d->objects[i]);
    }

    T *&operator[](int i)
    {
        return asQList()[i];
    }

    T *operator[](int i) const
    {
        return at(i);
    }

    void insert(int i, T* object)
    {
        Q_D(Private::MiObjectList);
        d->beginInsert(i, i);
        d->insert(i, object);
        d->endInsert(i, i);
    }

    void insert(int i, const QList<T*> &objects)
    {
        Q_D(Private::MiObjectList);
        const int end = i + objects.count() - 1;
        d->beginInsert(i, end);
        int j = i - 1;
        foreach (T* object, objects)
            d->insert(++j, object);
        d->endInsert(i, end);
    }

    void append(T* object)
    {
        insert(count(), object);
    }

    void append(const QList<T*> &objects)
    {
        insert(count(), objects);
    }

    void move(int i, int destination)
    {
        Q_D(Private::MiObjectList);
        d->beginMove(i, i, destination);
        d->objects.move(i, destination);
        d->endMove(i, i, destination);
    }

    void move(int i, int count, int destination)
    {
        Q_D(Private::MiObjectList);
        const int end = i + count - 1;
        d->beginMove(i, end, destination);
        QList<T*> taken;
        taken.reserve(count);
        for (int j = i;  j <= end;  ++j)
            taken.append(d->objects.takeAt(i));
        int k = destination - 1;
        foreach (QObject *object, taken)
            d->objects.insert(++k, object);
        d->endMove(i, end, destination);
    }

    void removeAt(int i)
    {
        Q_D(Private::MiObjectList);
        d->beginRemove(i, i);
        d->objects.removeAt(i);
        d->endRemove(i, i);
    }

    void removeAt(int i, int count)
    {
        Q_D(Private::MiObjectList);
        const int end = i + count - 1;
        d->beginRemove(i, end);
        for (int j = i;  j <= end;  ++j)
            d->objects.removeAt(j);
        d->endRemove(i, end);
    }

    void removeOne(const QObject* object)
    {
        Q_D(Private::MiObjectList);
        removeAt(d->objects.indexOf(object));
    }

    void clear()
    {
        removeAt(0, count());
    }

    QList<T*> toQList() const
    {
        Q_D(const Private::MiObjectList);
        return *reinterpret_cast<const QList<T*>*>(&d->objects);
    }

protected:
    QList<T*> &asQList()
    {
        Q_D(Private::MiObjectList);
        return reinterpret_cast<QList<T*>&>(d->objects);
    }

private:
    void setErased(bool erased)
    {
        MiObject::setErased(erased);
        Q_D(Private::MiObjectList);
        if (erased)
            foreach (QObject *object, d->objects) {
                MiObject *miObject = qobject_cast<MiObject*>(object);
                if (miObject)
                    miObject->erase();
            }
        else
            foreach (QObject *object, d->objects) {
                MiObject *miObject = qobject_cast<MiObject*>(object);
                if (miObject)
                    miObject->unerase();
            }
    }
};

template <typename T>
class MiSortedList : public MiList<T>
{
    Q_DISABLE_COPY(MiSortedList)

public:
    typedef MiObjectList::Properties Properties;

    explicit MiSortedList(QObject *parent = 0)
        :   MiList<T>(parent)
    {}

    virtual ~MiSortedList()
    {}

private:
    bool isSorted() const
    {
        const int end = MiList<T>::count() - 1;
        for (int i = 0;  i < end;  ++i)
            if (T::lessThan(MiList<T>::at(i + 1), MiList<T>::at(i)))
                return false;
        return true;
    }

    void sort()
    {
        if (isSorted())
            return;
        QList<T*> list = MiList<T>::toQList();
        MiList<T>::clear();
        qSort(list.begin(), list.end(), T::lessThan);
        append(list);
    }
};

#endif // MI_OBJECTLIST_H
