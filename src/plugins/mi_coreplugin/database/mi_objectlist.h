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

namespace Private {

class MiObjectListPrivate;

} // namespace Private

class MI_CORE_EXPORT MiObjectList : public MiObject
{
    Q_OBJECT

protected:
    MiObjectList(Private::MiObjectListPrivate &dd, QObject *parent)
        :   MiObject(parent)
        ,   d(&dd)
    {}

public:
    inline virtual ~MiObjectList();

signals:
    void objectsAboutToBeInserted(int start, int end);
    void objectsInserted(int start, int end);
    void objectsAboutToBeMoved(int start, int end, int destination);
    void objectsMoved(int start, int end, int destination);
    void objectsAboutToBeRemoved(int start, int end);
    void objectsRemoved(int start, int end);

private:
    Q_DISABLE_COPY(MiObjectList)

protected:
    friend class Private::MiObjectListPrivate;
    Private::MiObjectListPrivate *d;
};

namespace Private {

class MiObjectListPrivate
{
public:
    MiObjectList *q;
    QList<QObject*> objects;

    MiObjectListPrivate(MiObjectList *q)
        :   q(q)
    {}

    void insert(int i, QObject *object)
    {
        objects.insert(i, object);
        if (q != object->parent())
            object->setParent(q);
    }

    virtual void beginInsert(int start, int end)
    {
        q->emit objectsAboutToBeInserted(start, end);
    }

    virtual void endInsert(int start, int end)
    {
        q->emit objectsInserted(start, end);
    }

    virtual void beginMove(int start, int end, int destination)
    {
        q->emit objectsAboutToBeMoved(start, end, destination);
    }

    virtual void endMove(int start, int end, int destination)
    {
        q->emit objectsMoved(start, end, destination);
    }

    virtual void beginRemove(int start, int end)
    {
        q->emit objectsAboutToBeRemoved(start, end);
    }

    virtual void endRemove(int start, int end)
    {
        q->emit objectsRemoved(start, end);
    }
};

} // namespace Private

inline MiObjectList::~MiObjectList()
{
    qDebug() << Q_FUNC_INFO;
    delete d;
}

template <typename T>
class MiList : public MiObjectList
{
public:
    MiList(QObject *parent = 0)
        :   MiObjectList(*(new Private::MiObjectListPrivate(this)), parent)
    {}

protected:
    MiList(Private::MiObjectListPrivate &dd, QObject *parent)
        :   MiObjectList(dd, parent)
    {}

public:
    virtual ~MiList()
    {
        qDebug() << Q_FUNC_INFO;
    }

    bool isEmpty() const
    {
        return d->objects.isEmpty();
    }

    int count() const
    {
        return d->objects.count();
    }


    const QList<T*> &asQList() const
    {
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
        d->beginInsert(i, i);
        d->insert(i, object);
        d->endInsert(i, i);
    }

    void insert(int i, const QList<T*> &objects)
    {
        const int end = i + objects.count() - 1;
        d->beginInsert(i, end);
        int j = i - 1;
        foreach (T* object, objects)
            d->insert(++j, object);
        d->endInsert(i, end);
    }

    void insert(int i, const MiList<T> *objects)
    {
        insert(i, objects->asQList());
    }

    void append(T* object)
    {
        insert(count(), object);
    }

    void append(const QList<T*> &objects)
    {
        insert(count(), objects);
    }

    void append(const MiList<T> *objects)
    {
        append(objects->asQList());
    }

    void move(int i, int destination)
    {
        d->beginMove(i, i, destination);
        d->objects.move(i, destination);
        d->endMove(i, i, destination);
    }

    void move(int i, int count, int destination)
    {
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
        d->beginRemove(i, i);
        d->objects.removeAt(i);
        d->endRemove(i, i);
    }

    void removeAt(int i, int count)
    {
        const int end = i + count - 1;
        d->beginRemove(i, end);
        for (int j = i;  j <= end;  ++j)
            d->objects.removeAt(j);
        d->endRemove(i, end);
    }

    void removeOne(const T* object)
    {
        removeAt(d->objects.indexOf(object));
    }
};

#endif // MI_OBJECTLIST_H
