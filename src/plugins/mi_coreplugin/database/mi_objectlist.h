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
        ,   d_ptr(&dd)
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
    Private::MiObjectListPrivate *d_ptr;
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
    delete d_ptr;
}

namespace Private {

class MiWritableObjectListPrivate : public MiObjectListPrivate
{
public:
    bool erased;

    MiWritableObjectListPrivate(MiObjectList *q)
        :   MiObjectListPrivate(q)
        ,   erased(false)
    {}

    QList<MiWritableObjectInterface*> writableObjects() const
    {
        QList<MiWritableObjectInterface*> iobjects;
        foreach (QObject *qObject, objects) {
            MiObject *miObject = qobject_cast<MiObject*>(qObject);
            if (miObject && miObject->isWritable()) {
                MiWritableObjectInterface *iobject = dynamic_cast<MiWritableObjectInterface*>(miObject);
                Q_ASSERT(iobject);
                iobjects.append(iobject);
            }
        }
        return iobjects;
    }

    virtual void erase()
    {
        QList<MiWritableObjectInterface*> iobjects = writableObjects();
        foreach (MiWritableObjectInterface *iobject, iobjects)
            iobject->erase();
        erased = true;
    }

    virtual void unerase()
    {
        QList<MiWritableObjectInterface*> iobjects = writableObjects();
        foreach (MiWritableObjectInterface *iobject, iobjects)
            iobject->unerase();
        erased = false;
    }
};

} // namespace Private

class MiWritableObjectList : public MiObjectList
                           , public MiWritableObjectInterface
{
    Q_OBJECT

protected:
    MiWritableObjectList(Private::MiWritableObjectListPrivate &dd, QObject *parent)
        :   MiObjectList(dd, parent)
    {}

public:
    virtual ~MiWritableObjectList()
    {}

    virtual bool isWritable() const
    {
        return true;
    }

    virtual bool isErased() const
    {
        Q_D(const Private::MiWritableObjectList);
        return d->erased;
    }

    virtual void erase()
    {
        if (isErased())
            return;
        emit aboutToBeErased();
        Q_D(Private::MiWritableObjectList);
        d->erase();
        emit erased();
    }

    virtual void unerase()
    {
        if (!isErased())
            return;
        emit aboutToBeUnerased();
        Q_D(Private::MiWritableObjectList);
        d->unerase();
        emit unerased();
    }

    virtual bool read(QXmlStreamReader &in)
    {
        Q_ASSERT(false && "Not impemented yet.");
        Q_UNUSED(in);
        return false;
    }

    virtual void write(QXmlStreamReader &out) const
    {
        Q_ASSERT(false && "Not impemented yet.");
        Q_UNUSED(out);
    }

signals:
    void aboutToBeErased();
    void erased();
    void aboutToBeUnerased();
    void unerased();

private:
    Q_DISABLE_COPY(MiWritableObjectList)
    Q_DECLARE_PRIVATE(Private::MiWritableObjectList)
};

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
    {}

#include "mi_objectlist.hh"
};

template <typename T>
class MiWritableList : public MiWritableObjectList
{
public:
    MiWritableList(QObject *parent = 0)
        :   MiWritableObjectList(*(new Private::MiWritableObjectListPrivate(this)), parent)
    {}

protected:
    MiWritableList(Private::MiWritableObjectListPrivate &dd, QObject *parent)
        :   MiWritableObjectList(dd, parent)
    {}

public:
    virtual ~MiWritableList()
    {}

#include "mi_objectlist.hh"
};

#endif // MI_OBJECTLIST_H
