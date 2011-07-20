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

class MiObjectListPrivate : public MiObjectPrivate
{
    Q_DECLARE_PUBLIC(MiObject)

public:
    QList<MiListObject*> objects;

    MiObjectListPrivate(MiObject *q)
        :   MiObjectPrivate(q)
    {}

    virtual ~MiObjectListPrivate()
    {}

    void insert(int i, MiListObject *object)
    {
        Q_Q(MiObject);
        objects.insert(i, object);
        if (q != object->parent())
            object->setParent(q);
    }
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

    explicit MiObjectList(QObject *parent = 0)
        :   MiObject(*(new Private::MiObjectListPrivate(this)), parent)
    {}

    virtual ~MiObjectList()
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

    const MiListObject* at(int i) const
    {
        Q_D(const Private::MiObjectList);
        return d->objects.at(i);
    }

    MiListObject* &operator[](int i)
    {
        Q_D(Private::MiObjectList);
        return d->objects[i];
    }

    const MiListObject* operator[](int i) const
    {
        return at(i);
    }

    void insert(int i, MiListObject* object)
    {
        Q_D(Private::MiObjectList);
        beginInsert(i, i);
        d->insert(i, object);
        endInsert(i, i);
    }

    template <typename T>
    void insert(int i, const QList<T*> &objects)
    {
        Q_D(Private::MiObjectList);
        const int end = i + objects.count() - 1;
        beginInsert(i, end);
        int j = i - 1;
        foreach (T* object, objects)
            d->insert(++j, object);
        endInsert(i, end);
    }

    void append(MiListObject* object)
    {
        insert(count(), object);
    }

    template <typename T>
    void append(const QList<T*> &objects)
    {
        insert(count(), objects);
    }

    void removeAt(int i)
    {
        Q_D(Private::MiObjectList);
        beginRemove(i, i);
        d->objects.removeAt(i);
        endRemove(i, i);
    }

    void removeAt(int i, int count)
    {
        Q_D(Private::MiObjectList);
        const int end = i + count - 1;
        beginRemove(i, end);
        for (int j = i;  j <= end;  ++j)
            d->objects.removeAt(j);
        endRemove(i, end);
    }

    void removeOne(MiListObject* object)
    {
        Q_D(Private::MiObjectList);
        removeAt(d->objects.indexOf(object));
    }

    void clear()
    {
        removeAt(0, count());
    }

    template <typename T>
    QList<T*> toQList() const
    {
        Q_D(const Private::MiObjectList);
        return *reinterpret_cast<const QList<T*>*>(&d->objects);
    }

public slots:
    virtual void sort()
    {
        if (isSorted())
            return;
        Q_D(Private::MiObjectList);
        QList<MiListObject*> list = d->objects;
        clear();
        qSort(list.begin(), list.end(), lessThan);
        append(list);
    }

signals:
    void objectsAboutToBeInserted(int start, int end);
    void objectsInserted(int start, int end);
    void objectsAboutToBeRemoved(int start, int end);
    void objectsRemoved(int start, int end);

protected:
    bool isSorted() const
    {
        const int end = count() - 1;
        for (int i = 0;  i < end;  ++i)
            if (lessThan(at(i + 1), at(i)))
                return false;
        return true;
    }

    void beginInsert(int start, int end)
    {
        emit objectsAboutToBeInserted(start, end);
    }

    void endInsert(int start, int end)
    {
        emit objectsInserted(start, end);
        sort();
    }

    void beginRemove(int start, int end)
    {
        emit objectsAboutToBeRemoved(start, end);
    }

    void endRemove(int start, int end)
    {
        emit objectsRemoved(start, end);
    }

private:
    bool isList() const
    {
        return true;
    }

    void setErased(bool erased)
    {
        MiObject::setErased(erased);
        Q_D(Private::MiObjectList);
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

    static bool lessThan(const MiListObject *a, const MiListObject *b)
    {
        return a->lessThan(b);
    }
};

Q_DECLARE_METATYPE(MiObjectList*)

#endif // MI_OBJECTLIST_H
