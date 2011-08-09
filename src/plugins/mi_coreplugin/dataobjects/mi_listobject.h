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

#ifndef MI_LISTOBJECT_H
#define MI_LISTOBJECT_H

#include <mi_object.h>
#include <mi_scopedchange.h>

class MiListObjectPrivate;

class MI_CORE_EXPORT MiListObject : public MiObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    MiListObject(int propertyIndex = 0);

    ~MiListObject()
    {}

    const MiObjectList &children() const
    {
        return reinterpret_cast<const MiObjectList&>(QObject::children());
    }

    inline virtual void addChild(MiObject *child);
    inline virtual void removeChild(MiObject *child);

protected:
    MiListObject(MiListObjectPrivate &dd);

private:
    Q_DISABLE_COPY(MiListObject)
    Q_DECLARE_PRIVATE(MiListObject)
};

class MI_CORE_EXPORT MiListObjectPrivate : public MiObjectPrivate
{
    Q_DECLARE_PUBLIC(MiListObject)

public:
    const int propertyIndex;

    MiListObjectPrivate(MiListObject *q, int propertyIndex)
        :   MiObjectPrivate(q)
        ,   propertyIndex(propertyIndex)
    {}

    ~MiListObjectPrivate()
    {}

    template <typename T>
    QList<T*> &children() const
    {
        return reinterpret_cast<QList<T*>&>(const_cast<QObjectList&>(q_ptr->children()));
    }

    void addChild(MiObject *child)
    {
        Q_Q(MiListObject);
        q->addChild(child);
    }

    void removeChild(MiObject *child)
    {
        Q_Q(MiListObject);
        q->removeChild(child);
    }

    void beginChange(int i);
    void endChange(int i);

    void childChanged(int i)
    {
        Q_UNUSED(i);
        endChange(-1);
    }
};

inline MiListObject::MiListObject(int propertyIndex )
    :   MiObject(*(new MiListObjectPrivate(this, propertyIndex)))
{}

inline MiListObject::MiListObject(MiListObjectPrivate &dd)
    :   MiObject(dd)
{}

inline void MiListObject::addChild(MiObject *child)
{
    if (!child || children().contains(child))
        return;
    Q_D(MiListObject);
    changing(-1);
    d->MiObjectPrivate::addChild(child);
}

inline void MiListObject::removeChild(MiObject *child)
{
    if (!child || !children().contains(child))
        return;
    Q_D(MiListObject);
    changing(-1);
    d->MiObjectPrivate::removeChild(child);
}

Q_DECLARE_METATYPE(MiListObject*)

#endif // MI_LISTOBJECT_H
