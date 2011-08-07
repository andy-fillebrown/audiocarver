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
#include <QMetaType>

class MiListObjectPrivate;

class MI_CORE_EXPORT MiListObject : public MiObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    MiListObject(int propertyIndex = 0);

    virtual ~MiListObject()
    {}

    const QList<MiObject*> &children() const
    {
        return reinterpret_cast<const QList<MiObject*>&>(QObject::children());
    }

    inline virtual void addChild(MiObject *child);
    inline virtual void removeChild(MiObject *child);

protected:
    MiListObject(MiListObjectPrivate &dd);

private:
    Q_DISABLE_COPY(MiListObject)
    Q_DECLARE_PRIVATE(MiListObject)
};

class MiListObjectPrivate : public MiObjectPrivate
{
    Q_DECLARE_PUBLIC(MiListObject)

public:
    const int propertyIndex;

    MiListObjectPrivate(MiListObject *q, int propertyIndex)
        :   MiObjectPrivate(q)
        ,   propertyIndex(propertyIndex)
    {}

    virtual ~MiListObjectPrivate()
    {}

    virtual void notifyParentOfChange(int i = 0)
    {
        Q_UNUSED(i);
        MiObject *parent = q_ptr->parent();
        if (parent)
            parent->d_ptr->endChange(propertyIndex);
    }

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
    d->MiObjectPrivate::addChild(child);
    d->notifyParentOfChange();
}

inline void MiListObject::removeChild(MiObject *child)
{
    if (!child || !children().contains(child))
        return;
    Q_D(MiListObject);
    d->MiObjectPrivate::removeChild(child);
    d->notifyParentOfChange();
}

Q_DECLARE_METATYPE(MiListObject*)

#endif // MI_LISTOBJECT_H
