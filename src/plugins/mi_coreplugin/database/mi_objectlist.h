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
    Q_OBJECT

protected:
    MiObjectList(Private::MiObjectListData &dd, QObject *parent)
        :   MiObject(dd, parent)
    {}

public:
    virtual ~MiObjectList()
    {}

signals:
    void objectsAboutToBeInserted(int start, int end);
    void objectsInserted(int start, int end);
    void objectsAboutToBeMoved(int start, int end, int destination);
    void objectsMoved(int start, int end, int destination);
    void objectsAboutToBeRemoved(int start, int end);
    void objectsRemoved(int start, int end);

private:
    Q_DISABLE_COPY(MiObjectList)
    Q_DECLARE_PRIVATE(Private::MiObjectList)
};

namespace Private {

class MiObjectListPrivate : public MiObjectListData
{
public:
    MiObjectListPrivate(MiObject *q)
        :   MiObjectListData(q)
    {}

    virtual ~MiObjectListPrivate()
    {}

    void insert(int i, MiObject *object)
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

    virtual void erase()
    {
        MiObjectPrivate::erase();
        foreach (MiObject *object, objects)
            object->erase();
    }

    virtual void unerase()
    {
        MiObjectPrivate::unerase();
        foreach (MiObject *object, objects)
            object->unerase();
    }

private:
    Q_DECLARE_PUBLIC(MiObjectList)
};


class MiListPrivate : public MiObjectListPrivate
{
public:
    MiListPrivate(MiObjectList *q)
        :   MiObjectListPrivate(q)
    {}

    virtual ~MiListPrivate()
    {}
};

} // namespace Private

template <typename T>
class MiList : public MiObjectList
{
public:
    MiList(QObject *parent = 0)
        :   MiObjectList(*(new Private::MiListPrivate(this)), parent)
    {}

protected:
    MiList(Private::MiListPrivate &dd, QObject *parent)
        :   MiObjectList(dd, parent)
    {}

public:
    virtual ~MiList()
    {}


    bool isEmpty() const
    {
        Q_D(const Private::MiObjectList);
        return d->objects.isEmpty();
    }

    int count() const
    {
        Q_D(const Private::MiList);
        return d->objects.count();
    }

    const QList<T*> &asQList() const
    {
        Q_D(const Private::MiList);
        return reinterpret_cast<const QList<T*>&>(d->objects);
    }

    T *const &at(int i) const
    {
        return asQList().at(i);
    }

    T *&operator[](int i)
    {
        return asQList()[i];
    }

    const T *&operator[](int i) const
    {
        return at(i);
    }

    void insert(int i, T* object)
    {
        Q_D(Private::MiList);
        d->beginInsert(i, i);
        d->insert(i, object);
        d->endInsert(i, i);
    }

    void insert(int i, const QList<T*> &objects)
    {
        Q_D(const Private::MiList);
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
        Q_D(Private::MiList);
        d->beginMove(i, i, destination);
        d->objects.move(i, destination);
        d->endMove(i, i, destination);
    }

    void move(int i, int count, int destination)
    {
        Q_D(Private::MiList);
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
        Q_D(Private::MiList);
        d->beginRemove(i, i);
        d->objects.removeAt(i);
        d->endRemove(i, i);
    }

    void removeAt(int i, int count)
    {
        Q_D(Private::MiList);
        const int end = i + count - 1;
        d->beginRemove(i, end);
        for (int j = i;  j <= end;  ++j)
            d->objects.removeAt(j);
        d->endRemove(i, end);
    }

    void removeOne(const QObject* object)
    {
        Q_D(Private::MiList);
        removeAt(d->objects.indexOf(object));
    }

private:
    Q_DISABLE_COPY(MiList)
    Q_DECLARE_PRIVATE(Private::MiList)
};

#endif // MI_OBJECTLIST_H
