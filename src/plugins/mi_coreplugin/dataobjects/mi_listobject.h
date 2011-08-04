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

class MiListObjectPrivate : public MiObjectPrivate
{
    Q_DECLARE_PUBLIC(MiObject)

public:
    const int propertyIndex;

    MiListObjectPrivate(MiObject *q, int propertyIndex)
        :   MiObjectPrivate(q)
        ,   propertyIndex(propertyIndex)
    {}

    virtual ~MiListObjectPrivate()
    {}

    template <typename T>
    QList<T*> &children() const
    {
        return reinterpret_cast<QList<T*>&>(const_cast<QObjectList&>(q_ptr->children()));
    }

    virtual void notifyParentOfChange(int i = 0);
};

class MI_CORE_EXPORT MiListObject : public MiObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    MiListObject(int propertyIndex = 0)
        :   MiObject(*(new MiListObjectPrivate(this, propertyIndex)))
    {}

    virtual ~MiListObject()
    {}

    const QList<MiObject*> &children() const
    {
        return reinterpret_cast<const QList<MiObject*>&>(QObject::children());
    }

    virtual void addChild(MiObject *child)
    {
        if (!child || children().contains(child))
            return;
        Q_D(MiListObject);
        d->addChild(child);
        d->notifyParentOfChange();
    }

    virtual void removeChild(MiObject *child)
    {
        if (!child || !children().contains(child))
            return;
        Q_D(MiListObject);
        d->removeChild(child);
        d->notifyParentOfChange();
    }

protected:
    MiListObject(MiListObjectPrivate &dd)
        :   MiObject(dd)
    {}

private:
    Q_DISABLE_COPY(MiListObject)
    Q_DECLARE_PRIVATE(MiListObject)

    friend MiListObject *qobject_cast<MiListObject*>(QObject*);
};

inline void MiListObjectPrivate::notifyParentOfChange(int i)
{
    Q_UNUSED(i);
    MiListObject *parent = q_ptr->parent();
    if (parent)
        parent->d_ptr->endChange(propertyIndex);
}

Q_DECLARE_METATYPE(MiListObject*)

#endif // MI_LISTOBJECT_H
